/*
 * EntityFactory.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#include "EntityFactory.h"

LUA_REG_TYPE(EntityFactory);

EntityFactory::EntityFactory() {
	// TODO Auto-generated constructor stub

}

EntityFactory::~EntityFactory() {
	// TODO Auto-generated destructor stub
}

void EntityFactory::registerPrototype(const std::string& name, EntityPrototype creator) {
	if (creators.find(name) == creators.end()) {
		creators.insert({name, creator});
	}
}

EntityRef EntityFactory::create(const std::string& name) {
	if (creators.find(name) != creators.end()) {
		return creators.at(name)();
	}
	return nullptr;
}

void EntityFactory::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
			.beginClass<EntityFactory>("EntityFactory")
				.addFunction("registerPrototype", &EntityFactory::registerPrototype)
				.addFunction("create", &EntityFactory::create)
			.endClass()
		.endNamespace();
}
