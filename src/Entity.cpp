/*
 * Entity.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#include "Entity.h"

LUA_CLASS_REGISTER(Entity);

Entity::Entity() : x(0), y(0) {
}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

void Entity::registerLua(lua_State* l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
		.beginClass<Entity>("Entity")
			.addProperty("x", &Entity::getX)
			.addProperty("y", &Entity::getY)
			.addProperty("w", &Entity::getW)
			.addProperty("h", &Entity::getH)
			.addFunction("setPos", &Entity::setPos)
		.endClass()
	.endNamespace();
}

int Entity::getX() const {
	return x;
}

int Entity::getY() const {
	return y;
}

void Entity::setPos(int nx, int ny) {
	x = nx;
	y = ny;
}

int Entity::getW() const {
	return 0;
}

int Entity::getH() const {
	return 0;
}

void Entity::draw(GraphicsSurfaceRef s, int offx, int offy) {
	throw "Not a drawable";
}