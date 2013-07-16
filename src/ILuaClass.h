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
 
 class Something : LUA_CLASS(Something) {
 // ...
 public:
 LUA_CLASS_GET_SHARED(Something);
 };
 LUA_CLASS_SHARED_DEF(Something);
 
 Something.cpp:
 LUA_CLASS_REGISTER(Something);
 
 This will:
 - Add your class to the list of lua classes to be registered,
 when something calls ILuaClass::registerClasses it will register
 itself via the registerLua() method
 
 - Create a bunch of luabridge ContainerConstructionTraits magic to handle
 std::shared_ptr going between the c++/lua side.
 
*/

#define DEFAULT_NAMESPACE "game"

typedef std::function<void (lua_State*)> LuaRegisterFunc;

class ILuaClass {
public:
	virtual ~ILuaClass();
	static void registerLua(lua_State *l);

	static void registerClasses(lua_State *l);

	static void __addRegFunc(LuaRegisterFunc f);
private:
	static std::list<LuaRegisterFunc>* __regFuncs;
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

#define LUA_DERIVED_CLASS(T) public virtual ILuaClass
#define LUA_CLASS(T) LUA_DERIVED_CLASS(T), public std::enable_shared_from_this<T>
#define LUA_CLASS_GET_SHARED(T) inline std::shared_ptr<T> get_shared() { return shared_from_this(); }
#define LUA_CLASS_SHARED_DEF(T) \
	namespace luabridge { \
		template <> struct ContainerConstructionTraits<std::shared_ptr<T> > { \
			static std::shared_ptr<T> constructContainer(T *t) { \
				return t->get_shared(); \
			} \
		}; \
	}
#define LUA_CLASS_REGISTER(T) \
	class __luaReg##T { \
	public: \
		__luaReg##T() { Log::info("Added registration func for " #T); ILuaClass::__addRegFunc(&T::registerLua); } \
	}; \
	static __luaReg##T __s_luaReg##T;

#endif /* ILUACLASS_H_ */
