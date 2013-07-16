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

#include <memory>
#include "ILuaClass.h"

class World;
typedef std::shared_ptr<World> WorldRef;

class World : LUA_CLASS(World) {
public:
	World();
	virtual ~World();

	void spawnEntityAt(const std::string& type, int x, int y);
	void addEntity(EntityRef entity);
	void removeEntity(EntityRef entity);
	EntityFactoryRef getEntityFactory();

	void drawArea(GraphicsSurfaceRef s, int x, int y);

	static void registerLua(lua_State *l);

	LUA_CLASS_GET_SHARED(World);

protected:
	std::list<EntityRef> entities;

	EntityFactoryRef entFactory;
};

LUA_CLASS_SHARED_DEF(World);

#endif /* WORLD_H_ */
