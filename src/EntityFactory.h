/*
 * EntityFactory.h
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#ifndef ENTITYFACTORY_H_
#define ENTITYFACTORY_H_

#include "Entity.h"
#include "ILuaClass.h"

#include <functional>
#include <string>
#include <map>

class EntityFactory;
typedef std::shared_ptr<EntityFactory> EntityFactoryRef;

typedef std::function<EntityRef() > EntityPrototype;

class EntityFactory : public ILuaClass<EntityFactory> {
public:
	EntityFactory();
	virtual ~EntityFactory();

	void registerPrototype(const std::string& name, EntityPrototype creator);
	EntityRef create(const std::string& name);

	static void registerLua(lua_State *l);
private:
	std::map<const std::string, EntityPrototype> creators;
};

namespace luabridge {
	template <> struct Stack<EntityPrototype> {
		static void push(lua_State *l, EntityPrototype f) {
			throw "pushing EntityPrototype is not supported yet!";
		}
		
		static EntityPrototype get(lua_State *l, int index) {
			LuaRef func = Stack<LuaRef>::get(l, index);
			return [=]() -> EntityRef {
				//Log::info("about to pcall vm = %p, index = %d", l, index);
				return func();
			};
		}
	};
}

LUA_MAKE_REF(EntityFactory);

#endif /* ENTITYFACTORY_H_ */
