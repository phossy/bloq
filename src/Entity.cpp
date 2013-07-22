/*
 * Entity.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#include <stdexcept>

#include "Entity.h"

LUA_REG_TYPE(Entity);

Entity::Entity() : x(0), y(0), zOrder(0), entityId(0), boundLeft(0), boundRight(0), boundTop(0), boundBottom(0), collidable(false), type(""), collisionFunc(nullptr) {
}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

void Entity::registerLua(lua_State* l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
		.beginClass<Entity>("Entity")
			.addProperty("x", &Entity::getX, &Entity::setX)
			.addProperty("y", &Entity::getY, &Entity::setY)
			.addProperty("w", &Entity::getW)
			.addProperty("h", &Entity::getH)
			.addProperty("zOrder", &Entity::getZOrder, &Entity::setZOrder)
			.addProperty("id", &Entity::getId)
			.addProperty("type", &Entity::getType)
			.addProperty("collidable", &Entity::isCollidable, &Entity::setCollidable)
			.addProperty("onCollision", &Entity::getCollisionFunc, &Entity::setCollisionFunc)
			.addProperty("leftBound", &Entity::getLeftBound, &Entity::setLeftBound)
			.addProperty("rightBound", &Entity::getRightBound, &Entity::setRightBound)
			.addProperty("topBound", &Entity::getTopBound, &Entity::setTopBound)
			.addProperty("bottomBound", &Entity::getBottomBound, &Entity::setBottomBound)
		.endClass()
	.endNamespace();
}

int Entity::getX() const {
	return x;
}

int Entity::getY() const {
	return y;
}

int Entity::getZOrder() const {
	return zOrder;
}

void Entity::setX(int nx) {
	x = nx;
}

void Entity::setY(int ny) {
	y = ny;
}

void Entity::setZOrder(int nz) {
	zOrder = nz;
	
	// Tell the owning world to update its draw list accordingly
	if (owner != nullptr) {
		owner->updateZOrder();
	}
}

int Entity::getId() const {
	return entityId;
}

void Entity::setId(int newId) {
	entityId = newId;
}

const std::string& Entity::getType() const {
	return type;
}

void Entity::setType(const std::string& t) {
	type = t;
}

void Entity::setOwner(WorldRef w) {
	owner = w;
}

int Entity::getW() const {
	return 0;
}

int Entity::getH() const {
	return 0;
}

void Entity::draw(GraphicsSurfaceRef s, int offx, int offy) {
	throw std::runtime_error("Not a drawable");
}

void Entity::drawBoundingBox(GraphicsSurfaceRef s, int offx, int offy) {
	if (!collidable) {
		return; // don't bother for things with no collision detection
	}
	
	int w = getW();
	int h = getH();
	
	// left side
	s->drawRect(x + boundLeft - offx, y + boundTop - offy, 1, h - boundTop - boundBottom, COLOR_WHITE);
	
	// right side
	s->drawRect(x + w - boundRight - offx, y + boundTop - offy, 1, h - boundTop - boundBottom, COLOR_WHITE);
	
	// top side
	s->drawRect(x + boundLeft - offx, y + boundTop - offy, w - boundLeft - boundRight, 1, COLOR_WHITE);
	
	// bottom side
	s->drawRect(x + boundLeft - offx, y + h - boundBottom - offy, w - boundLeft - boundRight, 1, COLOR_WHITE);
}

int Entity::getLeftBound() const {
	return boundLeft;
}

int Entity::getRightBound() const {
	return boundRight;
}

int Entity::getTopBound() const {
	return boundTop;
}

int Entity::getBottomBound() const {
	return boundBottom;
}

void Entity::setLeftBound(int off) {
	boundLeft = off;
}

void Entity::setRightBound(int off) {
	boundRight = off;
}

void Entity::setTopBound(int off) {
	boundTop = off;
}

void Entity::setBottomBound(int off) {
	boundBottom = off;
}

bool Entity::isCollidable() const {
	return collidable;
}

void Entity::setCollidable(bool on) {
	collidable = on;
}

EntityCollisionFunction Entity::getCollisionFunc() const {
	return collisionFunc;
}

void Entity::setCollisionFunc(EntityCollisionFunction f) {
	collisionFunc = f;
}
