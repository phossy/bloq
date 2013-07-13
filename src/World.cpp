/*
 * World.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: jason
 */

#include "World.h"

World::World() {
	entFactory = std::unique_ptr<EntityFactory>(new EntityFactory());
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::spawnEntityAt(const std::string& type, int x, int y) {
	auto pEnt = entFactory->create(type);
	pEnt->setPos(x, y);
	addEntity(pEnt);
}

void World::addEntity(std::shared_ptr<Entity> entity) {
	entities.push_back(entity);
}

void World::removeEntity(std::shared_ptr<Entity> entity) {
	entities.remove(entity);
}

EntityFactory& World::getEntityFactory() {
	return *entFactory;
}

void World::drawArea(GraphicsSurface& s, int x, int y) {
	int w = s.getW();
	int h = s.getH();

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
