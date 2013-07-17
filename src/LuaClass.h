/*
 * LuaClass.h
 *
 *  Created on: Jul 15, 2013
 *      Author: jason
 */

#ifndef LUACLASS_H_
#define LUACLASS_H_

#include <functional>
#include <memory>
#include <list>

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
	virtual ~LuaClass() {
		//Log::info("Managed class instance %s [%p] destroyed", typeid(this).name(), this);
	}
	
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

	// Stack specialization for getting std::function<> from lua (so we can call lua closures from C++)
	template <class R, class... A> struct Stack<std::function<R(A...)> > {
		static void push(lua_State *l, std::function<R(A...)> f) {
			throw "Pushing std::function<R(A...)> is not supported";
		}
		static std::function<R(A...)> get(lua_State *l, int index) {
			LuaRef f = Stack<LuaRef>::get(l, index);
			return [f](A... args) {
				return f(args...);
			};
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
