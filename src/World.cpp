/*
 * World.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: jason
 */

#include "World.h"

LUA_REG_TYPE(World);

World::World() : drawBoundingBoxes(false) {
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
			.addFunction("findEntity", &World::findEntity)
			.addProperty("entityFactory", &World::getEntityFactory)
			.addFunction("addEntity", &World::addEntity)
			.addFunction("removeEntity", &World::removeEntity)
			.addProperty("drawBoundingBoxes", &World::getDrawBoundingBoxes, &World::setDrawBoundingBoxes)
		.endClass()
	.endNamespace();
}

EntityRef World::spawnEntityAt(const std::string& type, int x, int y, int zOrder) {
	auto pEnt = entFactory->create(type);
	if (pEnt == nullptr) {
		throw std::runtime_error("Failed to create entity");
	}
	addEntity(pEnt);
	
	// Note that we add the entity before setting x/y/z, so we get registered as the owner
	// causing it to refresh the z-order when we call setZOrder() below
	pEnt->setX(x);
	pEnt->setY(y);
	pEnt->setZOrder(zOrder); // causes z-order refresh
	return pEnt;
}

void World::addEntity(EntityRef entity) {
	// can't have id = 0
	if (entity->getId() == 0) {
		throw std::logic_error("Entity does not have an ID assigned");
	}
	
	// can't have a missing type
	if (entity->getType().length() == 0) {
		throw std::logic_error("Entity does not have a type assigned");
	}
	
	// check for one that already exists with the same ID
	for (auto &e : entities) {
		if (e == entity || e->getId() == entity->getId()) {
			throw std::logic_error("Cannot add entity with a duplicate ID");
		}
	}
	
	entity->setOwner(shared_from_this());
	// update z-order accordingly
	updateZOrder();
	
	entities.push_back(entity);
}

void World::removeEntity(EntityRef entity) {
	// note this only schedules an entity for deletion in the main loop,
	// to avoid messing with entities we may be iterating over
	removalQueue.push_back(entity);
}

void World::drainRemovalQueue() {
	// called from main loop only
	for (auto &i : removalQueue) {
		entities.remove(i);
		i->setOwner(nullptr);
	}
	removalQueue.clear();
}

EntityFactoryRef World::getEntityFactory() const {
	return entFactory;
}

EntityRef World::findEntity(int entityId) {
	for (auto &e : entities) {
		if (e->getId() == entityId) {
			return e;
		}
	}
	return nullptr;
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
			
			// draw bounding box for it too if so requested
			if (drawBoundingBoxes) {
				e->drawBoundingBox(s, x, y);
			}
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

/**
 Called every tick to check for entities that have collided and react appropriately.
 */
void World::checkAndNotifyCollidedEntities() {
	for (auto &e : entities) {
		if (e->isCollidable()) {
			int ex1 = e->getX() + e->getLeftBound();
			int ey1 = e->getY() + e->getTopBound();
			int ex2 = e->getX() + e->getW() - e->getRightBound();
			int ey2 = e->getY() + e->getH() - e->getBottomBound();
			
			// scan through the list for any candidates that are touching this one
			for (auto &c : entities) {
				if (c != e && c->isCollidable()) {
					// check for bounding box overlap
					int cx1 = c->getX() + c->getLeftBound();
					int cy1 = c->getY() + c->getTopBound();
					int cx2 = c->getX() + c->getW() - c->getRightBound();
					int cy2 = c->getY() + c->getH() - c->getBottomBound();
					
					if (ex1 <= cx2 && ex2 >= cx1 && ey1 <= cy2 && ey2 >= cy1) {
						// collided, notify e
						EntityCollisionFunction f = e->getCollisionFunc();
						if (f != nullptr) {
							f(c);
						}
					}
				}
			}
		}
	}
}

bool World::getDrawBoundingBoxes() const {
	return drawBoundingBoxes;
}

void World::setDrawBoundingBoxes(bool on) {
	drawBoundingBoxes = on;
}
