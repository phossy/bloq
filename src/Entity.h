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

class Entity {
public:
	Entity();
	virtual ~Entity();
	int getX();
	int getY();
	void setPos(int nx, int ny);
	virtual int getW();
	virtual int getH();
	virtual void draw(GraphicsSurface& s, int offx, int offy);
protected:
	int x;
	int y;
};

#endif /* ENTITY_H_ */
