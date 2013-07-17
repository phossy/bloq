/*
 * EntityFactory.h
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#ifndef ENTITYFACTORY_H_
#define ENTITYFACTORY_H_

#include "Entity.h"
#include "LuaClass.h"

#include <functional>
#include <string>
#include <map>

class EntityFactory;
typedef std::shared_ptr<EntityFactory> EntityFactoryRef;

typedef std::function<EntityRef() > EntityPrototype;

class EntityFactory : public LuaClass<EntityFactory> {
public:
	EntityFactory();
	virtual ~EntityFactory();

	void registerPrototype(const std::string& name, EntityPrototype creator);
	EntityRef create(const std::string& name);

	static void registerLua(lua_State *l);
private:
	std::map<const std::string, EntityPrototype> creators;
};

#endif /* ENTITYFACTORY_H_ */
