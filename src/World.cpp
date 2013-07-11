/*
 * World.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: jason
 */

#include "World.h"

World::World() {
	// TODO Auto-generated constructor stub

}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::addEntity(const Entity* entity) {
	entities.push_back(entity);
}

void World::removeEntity(const Entity* entity) {
	entities.remove(entity);
}
