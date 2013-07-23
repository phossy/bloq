/*
 * ShapeEntity.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: jason
 */

#include <stdexcept>

#include "ShapeEntity.h"
#include "Log.h"

LUA_REG_TYPE(ShapeEntity);

ShapeEntity::ShapeEntity(const RGBAColor& c) : color(c), w(0), h(0) {
}

ShapeEntity::~ShapeEntity() {
	// TODO Auto-generated destructor stub
}

void ShapeEntity::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
		.deriveClass<ShapeEntity, Entity>("ShapeEntity")
			.addConstructor<void(*)(const RGBAColor&), ShapeEntityRef>()
			.addProperty("w", &ShapeEntity::getW, &ShapeEntity::setW)
			.addProperty("h", &ShapeEntity::getH, &ShapeEntity::setH)
		.endClass()
	.endNamespace();
}

void ShapeEntity::draw(GraphicsSurfaceRef s, int offx, int offy) {
	//s->drawRect(x - offx, y - offy, w, h, color);
	s->drawRect(x - offx, y - offy, 1, h, color); // left
	s->drawRect(x - offx + w - 1, y - offy, 1, h, color); // right
	s->drawRect(x - offx, y - offy, w, 1, color); // top
	s->drawRect(x - offx, y - offy + h - 1, w, 1, color); // bottom
}

int ShapeEntity::getW() const {
	return w;
}

int ShapeEntity::getH() const {
	return h;
}

void ShapeEntity::setW(int nw) {
	w = nw;
}

void ShapeEntity::setH(int nh) {
	h = nh;
}
