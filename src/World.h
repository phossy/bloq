/*
 * World.h
 *
 *  Created on: Jul 10, 2013
 *      Author: jason
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <memory>
#include <list>

class World;
typedef std::shared_ptr<World> WorldRef;

#include "LuaClass.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "GraphicsSurface.h"

class World : public LuaClass<World> {
public:
	World();
	virtual ~World();

	EntityRef spawnEntityAt(const std::string& type, int x, int y, int zOrder);
	EntityRef findEntity(int entityId);
	void addEntity(EntityRef entity);
	void removeEntity(EntityRef entity);
	EntityFactoryRef getEntityFactory() const;
	void drawArea(GraphicsSurfaceRef s, int x, int y);
	void updateZOrder();
	
	void checkAndNotifyCollidedEntities();
	void drainRemovalQueue();
	
	bool getDrawBoundingBoxes() const;
	void setDrawBoundingBoxes(bool on);

	static void registerLua(lua_State *l);
	
protected:
	std::list<EntityRef> entities;
	std::list<EntityRef> removalQueue;
	EntityFactoryRef entFactory;
	bool drawBoundingBoxes;
};

#endif /* WORLD_H_ */
