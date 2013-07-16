/*
 * World.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: jason
 */

#include "World.h"

LUA_CLASS_REGISTER(World);

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
			//.addFunction("addEntity", &World::addEntity)
			//.addFunction("removeEntity", &World::removeEntity)
		.endClass()
	.endNamespace();
}

void World::spawnEntityAt(const std::string& type, int x, int y) {
	auto pEnt = entFactory->create(type);
	pEnt->setPos(x, y);
	addEntity(pEnt);
}

void World::addEntity(EntityRef entity) {
	entities.push_back(entity);
}

void World::removeEntity(EntityRef entity) {
	entities.remove(entity);
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
