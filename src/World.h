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
	void addEntity(std::shared_ptr<Entity> entity);
	void removeEntity(std::shared_ptr<Entity> entity);
	EntityFactory& getEntityFactory();

	void drawArea(GraphicsSurface& s, int x, int y);

	static void registerLua(lua_State *L);

	//WorldRef get_shared() { return shared_from_this(); }
	LUA_CLASS_GET_SHARED(World);

protected:
	std::list<std::shared_ptr<Entity> > entities;

	std::unique_ptr<EntityFactory> entFactory;
};

LUA_CLASS_DEF(World);

#endif /* WORLD_H_ */
