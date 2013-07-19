/*
 * Entity.h
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <memory>

class Entity;
typedef std::shared_ptr<Entity> EntityRef;

#include "GraphicsSurface.h"
#include "LuaClass.h"
#include "World.h"

class Entity : public LuaClass<Entity> {
public:
	Entity();
	virtual ~Entity();
	int getX() const;
	int getY() const;
	void setX(int nx);
	void setY(int ny);
	int getZOrder() const;
	void setZOrder(int nz);
	void setOwner(WorldRef w);
	virtual int getW() const;
	virtual int getH() const;
	virtual void draw(GraphicsSurfaceRef s, int offx, int offy);
	
	static void registerLua(lua_State* l);
protected:
	int x;
	int y;
	int zOrder;
	WorldRef owner;
};

#endif /* ENTITY_H_ */
