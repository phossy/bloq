/*
 * ILuaClass.h
 *
 *  Created on: Jul 15, 2013
 *      Author: jason
 */

#ifndef ILUACLASS_H_
#define ILUACLASS_H_

#include <functional>
#include <memory>
#include <list>

#include <luajit-2.0/lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include "Log.h"

/**
 Define your class like so:
 Something.h:
 
 class Something : public ILuaClass<Something> {
 // ...
 };
 LUA_MAKE_REF(Something);
 
 Something.cpp:
 LUA_REG_TYPE(Something);
 
 This will:
 - Add your class to the list of lua classes to be registered,
 when something calls ILuaClassImpl::__registerClasses it will register
 itself via the registerLua() method
 
 - Create a bunch of luabridge ContainerConstructionTraits magic to handle
 std::shared_ptr going between the c++/lua side.
*/

#define DEFAULT_NAMESPACE "game"

typedef std::function<void (lua_State*)> LuaRegisterFunc;

// Silly hack to allow multiple base classes with enable_shared_from_this.
// See http://stackoverflow.com/a/12793989
class virt_enable_shared_from_this : public std::enable_shared_from_this<virt_enable_shared_from_this> {
public:
	virtual ~virt_enable_shared_from_this() {}
};

class ILuaClassImpl {
public:
	virtual ~ILuaClassImpl();
	static void registerLua(lua_State *l);
	
	static void __registerClasses(lua_State *l);
	static void __addRegFunc(LuaRegisterFunc f);
private:
	static std::list<LuaRegisterFunc>* __regFuncs;
};

template <class T> class ILuaClass : virtual public virt_enable_shared_from_this, public ILuaClassImpl {
public:
	virtual ~ILuaClass() {}
	
	std::shared_ptr<T> shared_from_this() {
		return std::dynamic_pointer_cast<T>(virt_enable_shared_from_this::shared_from_this());
	}
};

namespace luabridge {
	template <class T> struct ContainerTraits<std::shared_ptr<T> > {
		typedef T Type;
		static T* get(std::shared_ptr<T> const& c) {
			return c.get();
		}
	};

	template <class T> struct ContainerConstructionTraits<std::shared_ptr<T> > {};
}

#define LUA_MAKE_REF(T) \
	namespace luabridge { \
		template <> struct ContainerConstructionTraits<T##Ref> { \
			static T##Ref constructContainer(T *t) { \
				return t->ILuaClass<T>::shared_from_this(); \
			} \
		}; \
	}
#define LUA_REG_TYPE(T) \
	class __luaReg##T { \
	public: \
		__luaReg##T() { Log::info("Added registration func for " #T); ILuaClass<T>::__addRegFunc(&T::registerLua); } \
	}; \
	static __luaReg##T __s_luaReg##T;

#endif /* ILUACLASS_H_ */
