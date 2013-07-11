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

class World {
public:
	World();
	virtual ~World();

	void addEntity(const Entity* entity);
	void removeEntity(const Entity* entity);
protected:
	std::list<const Entity*> entities;
};

#endif /* WORLD_H_ */
