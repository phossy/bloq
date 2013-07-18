/*
 * World.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: jason
 */

#include "World.h"

LUA_REG_TYPE(World);

World::World() {
	entFactory = std::make_shared<EntityFactory>();
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
		.beginClass<World>("World")
			.addFunction("spawnEntityAt", &World::spawnEntityAt)
			.addFunction("getEntityFactory", &World::getEntityFactory)
			.addFunction("addEntity", &World::addEntity)
			.addFunction("removeEntity", &World::removeEntity)
		.endClass()
	.endNamespace();
}

EntityRef World::spawnEntityAt(const std::string& type, int x, int y, int zOrder) {
	auto pEnt = entFactory->create(type);
	addEntity(pEnt);
	
	// Note that we add the entity before setting x/y/z, so we get registered as the owner
	// causing it to refresh the z-order when we call setZOrder() below
	pEnt->setPos(x, y);
	pEnt->setZOrder(zOrder); // causes z-order refresh
	return pEnt;
}

void World::addEntity(EntityRef entity) {
	entity->setOwner(shared_from_this());
	// update z-order accordingly
	updateZOrder();
	
	entities.push_back(entity);
}

void World::removeEntity(EntityRef entity) {
	entities.remove(entity);
	entity->setOwner(nullptr);
}

EntityFactoryRef World::getEntityFactory() {
	return entFactory;
}

void World::drawArea(GraphicsSurfaceRef s, int x, int y) {
	int w = s->getW();
	int h = s->getH();

	for (auto &e : entities) {
		// bounds check to see whether part of the entity is visible on the screen
		int ex = e->getX();
		int ey = e->getY();
		
		if ((ex >= (x - e->getW()) && ex <= (x + w)) &&
			(ey >= (y - e->getH()) && ey <= (y + h))) {
			// visible, draw it
			e->draw(s, x, y);
		}
	}
}

/**
 Typically, this would be called by Entity when it updates its z-order to cause
 the World to re-sort its list appropriately.
 */
void World::updateZOrder() {
	entities.sort([&](EntityRef first, EntityRef second) -> bool {
		return (first->getZOrder() < second->getZOrder());
	});
}
