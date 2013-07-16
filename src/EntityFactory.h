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

class EntityFactory : LUA_CLASS(EntityFactory) {
public:
	EntityFactory();
	virtual ~EntityFactory();

	void registerPrototype(const std::string& name, EntityPrototype creator);
	EntityRef create(const std::string& name);

	LUA_CLASS_GET_SHARED(EntityFactory);
	static void registerLua(lua_State *l);
private:
	std::map<const std::string, EntityPrototype> creators;
};

LUA_CLASS_SHARED_DEF(EntityFactory);

#endif /* ENTITYFACTORY_H_ */
