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

const EntityFactory& World::getEntityFactory() {
	return *entFactory;
}

void World::drawArea(GraphicsSurface& s, int x, int y) {
	int w = s.getW();
	int h = s.getH();

	int maxVisibleX = x + w;
	int maxVisibleY = y + h;

	for (auto &i : entities) {
		// bounds check to see whether part of the entity is visible on the screen
		int entX = i->getX();
		int entY = i->getY();
		int entMaxX = entX + i->getW();
		int entMaxY = entY + i->getH();


	}
}
