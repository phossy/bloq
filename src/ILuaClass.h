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

typedef std::function<void (lua_State*)> LuaRegistrationFunc;

class ILuaClass {
public:
	virtual ~ILuaClass();
	static void registerLua(lua_State *l);

	static void callRegistrationFuncs(lua_State *l);

	static void __addRegistrationFunc(LuaRegistrationFunc f);
private:
	static std::list<LuaRegistrationFunc>* __regFuncs;
};

namespace luabridge {
	template <class T> struct ContainerTraits<std::shared_ptr<T> > {
		static T* get(std::shared_ptr<T> const& c) {
			return c.get();
		}
	};

	template <class T> struct ContainerConstructionTraits<std::shared_ptr<T> > {};
}

#define LUA_CLASS(T) public ILuaClass, public std::enable_shared_from_this<T>
#define LUA_CLASS_GET_SHARED(T) inline std::shared_ptr<T> get_shared() { return shared_from_this(); }
#define LUA_CLASS_DEF(T) \
	namespace luabridge { \
		template <> struct ContainerConstructionTraits<std::shared_ptr<T> > { \
			static std::shared_ptr<T> constructContainer(T *t) { \
				return t->get_shared(); \
			} \
		}; \
	} \
	class T::__LuaReg { \
	public: \
		__LuaReg() { Log::info("Added registration func for " #T); ILuaClass::__addRegistrationFunc(&T::registerLua); } \
	}; \
	static T::__LuaReg##T __var_luaReg##T;

#endif /* ILUACLASS_H_ */
