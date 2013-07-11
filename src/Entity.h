/*
 * Entity.h
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <memory>

class Entity {
public:
	Entity();
	virtual ~Entity();
	int getX();
	int getY();
	void setPos(int nx, int ny);
protected:
	int x;
	int y;
};

#endif /* ENTITY_H_ */
