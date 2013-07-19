/*
 * LuaClass.h
 *
 *  Created on: Jul 15, 2013
 *      Author: jason
 */

#ifndef LUACLASS_H_
#define LUACLASS_H_

#include <stdexcept>
#include <functional>
#include <memory>
#include <list>
#include <utility>

#include <luajit-2.0/lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include "Log.h"

/**
 Define your class like so:
 Something.h:
 
 class Something : public LuaClass<Something> {
 // ...
 };
 
 Something.cpp:
 LUA_REG_TYPE(Something);
 
 This will:
 - Add your class to the list of lua classes to be registered,
 when something calls LuaClassImpl::__registerClasses it will register
 itself via the registerLua() method
*/

#define DEFAULT_NAMESPACE "game"

typedef std::function<void (lua_State*)> LuaRegisterFunc;

// Silly hack to allow multiple base classes with enable_shared_from_this.
// See http://stackoverflow.com/a/12793989
class virt_enable_shared_from_this : public std::enable_shared_from_this<virt_enable_shared_from_this> {
public:
	virtual ~virt_enable_shared_from_this() {}
};

class LuaClassImpl {
public:
	virtual ~LuaClassImpl();
	
	static void __registerClasses(lua_State *l);
	static void __addRegFunc(LuaRegisterFunc f);
private:
	static std::list<LuaRegisterFunc>* __regFuncs;
};

template <class T> class LuaClass : public virtual virt_enable_shared_from_this, public LuaClassImpl {
public:
	virtual ~LuaClass() {}
	
	static void registerLua(lua_State *l);

	std::shared_ptr<T> shared_from_this() {
		return std::dynamic_pointer_cast<T>(virt_enable_shared_from_this::shared_from_this());
	}
};

namespace luabridge {
	// specialization for std::shared_ptr to allow those being passed across the C++/Lua side
	template <class T> struct ContainerTraits<std::shared_ptr<T> > {
		typedef T Type;
		static T* get(std::shared_ptr<T> const& c) {
			return c.get();
		}
	};
	template <class T> struct ContainerConstructionTraits<std::shared_ptr<T> > {
		static std::shared_ptr<T> constructContainer(T *t) {
			return ((LuaClass<T>*)t)->shared_from_this();
		}
	};

	// Stack specialization for getting std::function<A...> from lua
	// (so we can call lua closures from C++) with no return value
	template <class... A> struct Stack<std::function<void(A...)> > {
		static void push(lua_State *l, std::function<void(A...)> f) {
			throw std::runtime_error("Pushing std::function<void(A...)> is not supported");
		}
		static std::function<void(A...)> get(lua_State *l, int index) {
			LuaRef f = Stack<LuaRef>::get(l, index);
			return [f](A... args) {
				f(args...);
			};
		}
	};
	// Specialization for std::function<A...> returning an arbitrary type
	// (Clang needs this specifically since it fails to infer the lambda return type
	// without the -> R, and return ...; from a void function isn't allowed)
	template <class R, class... A> struct Stack<std::function<R(A...)> > {
		static void push(lua_State *l, std::function<R(A...)> f) {
			throw std::runtime_error("Pushing std::function<R(A...)> is not supported");
		}
		static std::function<R(A...)> get(lua_State *l, int index) {
			LuaRef f = Stack<LuaRef>::get(l, index);
			return [f](A... args) -> R {
				return f(args...);
			};
		}
	};

	// Specialization for std::pair<A, B> <--> indexed table
	template <class A, class B> struct Stack<std::pair<A, B> > {
		static void push(lua_State *l, std::pair<A, B> p) {
			LuaRef ref = newTable(l);
			ref[1] = p.first;
			ref[2] = p.second;
			Stack<LuaRef>::push(l, ref);
		}
		static std::pair<A, B> get(lua_State *l, int index) {
			LuaRef t = Stack<LuaRef>::get(l, index);
			//assert(t.isTable()); // TODO more robust error handling?
			return std::make_pair(static_cast<A>(t[1]), static_cast<B>(t[2]));
		}
	};

	// Specialization for std::tuple<A, B, C> <--> indexed table
	template <class A, class B, class C> struct Stack<std::tuple<A, B, C> const&> {
		static void push(lua_State *l, std::tuple<A, B, C> const& t) {
			LuaRef ref = newTable(l);
			ref[1] = std::get<0>(t);
			ref[2] = std::get<1>(t);
			ref[3] = std::get<2>(t);
			Stack<LuaRef>::push(l, ref);
		}
		static std::tuple<A, B, C> const get(lua_State *l, int index) {
			LuaRef t = Stack<LuaRef>::get(l, index);
			//assert(t.isTable() && t.length() == 3); // TODO more robust error handling?
			return std::make_tuple(static_cast<A>(t[1]), static_cast<B>(t[2]), static_cast<C>(t[3]));
		}
	};
	
	// Specialization for std::tuple<A, B, C, D> <--> indexed table
	template <class A, class B, class C, class D> struct Stack<std::tuple<A, B, C, D> const&> {
		static void push(lua_State *l, std::tuple<A, B, C, D> const& t) {
			LuaRef ref = newTable(l);
			ref[1] = std::get<0>(t);
			ref[2] = std::get<1>(t);
			ref[3] = std::get<2>(t);
			ref[4] = std::get<3>(t);
			Stack<LuaRef>::push(l, ref);
		}
		static std::tuple<A, B, C, D> const get(lua_State *l, int index) {
			LuaRef t = Stack<LuaRef>::get(l, index);
			//assert(t.isTable() && t.length() == 4); // TODO more robust error handling?
			return std::make_tuple(static_cast<A>(t[1]), static_cast<B>(t[2]), static_cast<C>(t[3]), static_cast<D>(t[4]));
		}
	};
	// Pass-by-value version of the above
	template <class A, class B, class C, class D> struct Stack<std::tuple<A, B, C, D> > {
		static void push(lua_State *l, std::tuple<A, B, C, D> t) {
			Stack<std::tuple<A, B, C, D> const&>::push(l, t);
		}
		
		static std::tuple<A, B, C, D> get(lua_State *l, int index) {
			return Stack<std::tuple<A, B, C, D> const&>::get(l, index);			
		}
	};
}

// Defines the static initializer to call the registration function.
#define LUA_REG_TYPE(T) \
	static class __luaReg##T { \
	public: \
		__luaReg##T() { Log::info("Added registration func for " #T); LuaClass<T>::__addRegFunc(&T::registerLua); } \
	} __s_luaReg##T;

#endif /* LUACLASS_H_ */
