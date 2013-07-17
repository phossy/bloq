/*
 * Entity.h
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <memory>
#include "GraphicsSurface.h"
#include "LuaClass.h"

class Entity;
typedef std::shared_ptr<Entity> EntityRef;

class Entity : public LuaClass<Entity> {
public:
	Entity();
	virtual ~Entity();
	int getX() const;
	int getY() const;
	void setPos(int nx, int ny);
	virtual int getW() const;
	virtual int getH() const;
	virtual void draw(GraphicsSurfaceRef s, int offx, int offy);
	
	static void registerLua(lua_State* l);
protected:
	int x;
	int y;
};

#endif /* ENTITY_H_ */
