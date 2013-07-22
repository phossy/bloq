/*
 * Entity.h
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <memory>
#include <functional>
#include <string>

class Entity;
typedef std::shared_ptr<Entity> EntityRef;

#include "GraphicsSurface.h"
#include "LuaClass.h"
#include "World.h"

typedef std::function<void(EntityRef collidingEntity)> EntityCollisionFunction;

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
	int getId() const;
	void setId(int newId);
	const std::string& getType() const;
	void setType(const std::string& t);
	virtual int getW() const;
	virtual int getH() const;
	virtual void draw(GraphicsSurfaceRef s, int offx, int offy);
	virtual void drawBoundingBox(GraphicsSurfaceRef s, int offx, int offy);
	
	// bounding box for collision detection
	int getLeftBound() const;
	int getRightBound() const;
	int getTopBound() const;
	int getBottomBound() const;
	
	void setLeftBound(int off);
	void setRightBound(int off);
	void setTopBound(int off);
	void setBottomBound(int off);
	
	bool isCollidable() const;
	void setCollidable(bool on);
	
	EntityCollisionFunction getCollisionFunc() const;
	void setCollisionFunc(EntityCollisionFunction f);
	
	static void registerLua(lua_State* l);
protected:
	int x;
	int y;
	int zOrder;
	int entityId; // must be unique in a World
	WorldRef owner;
	int boundLeft, boundRight, boundTop, boundBottom;
	bool collidable;
	std::string type; // must be assigned
	
	EntityCollisionFunction collisionFunc;
};

#endif /* ENTITY_H_ */
