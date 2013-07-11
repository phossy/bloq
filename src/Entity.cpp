/*
 * Entity.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#include "Entity.h"

Entity::Entity() : x(0), y(0) {
}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

int Entity::getX() {
	return x;
}

int Entity::getY() {
	return y;
}

void Entity::setPos(int nx, int ny) {
	x = nx;
	y = ny;
}
