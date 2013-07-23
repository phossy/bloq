/*
 * ShapeEntity.h
 *
 *  Created on: Jul 22, 2013
 *      Author: jason
 */

#ifndef SHAPEENTITY_H_
#define SHAPEENTITY_H_

#include <memory>
#include <vector>

class ShapeEntity;
typedef std::shared_ptr<ShapeEntity> ShapeEntityRef;

#include "Entity.h"
#include "LuaClass.h"

class ShapeEntity: public Entity, public LuaClass<ShapeEntity> {
public:
	ShapeEntity(const RGBAColor& c);
	virtual ~ShapeEntity();
	virtual void draw(GraphicsSurfaceRef s, int offx, int offy);
	virtual int getW() const;
	virtual int getH() const;
	void setW(int nw);
	void setH(int nh);

	static void registerLua(lua_State *l);
	
protected:
	RGBAColor color;
	int w, h;
};

#endif /* SHAPEENTITY_H_ */
