/*
 * World.h
 *
 *  Created on: Jul 10, 2013
 *      Author: jason
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <list>
#include "Entity.h"
#include "EntityFactory.h"
#include "GraphicsSurface.h"

class World {
public:
	World();
	virtual ~World();

	void spawnEntityAt(const std::string& type, int x, int y);
	void addEntity(std::shared_ptr<Entity> entity);
	void removeEntity(std::shared_ptr<Entity> entity);
	const EntityFactory& getEntityFactory();

	void drawArea(GraphicsSurface& s, int x, int y);

protected:
	std::list<std::shared_ptr<Entity> > entities;

	std::unique_ptr<EntityFactory> entFactory;
};

#endif /* WORLD_H_ */