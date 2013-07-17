/*
 * SpriteEntity.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#include "SpriteEntity.h"
#include "Log.h"

LUA_REG_TYPE(SpriteEntity);

SpriteEntity::SpriteEntity() : frame(0) {
}

SpriteEntity::SpriteEntity(std::initializer_list<BitmapRef> bmps) : frame(0), bitmaps(bmps) {
}

SpriteEntity::SpriteEntity(lua_State *l) : frame(0) {
	int n = lua_gettop(l);
	Log::debug("SpriteEntity::SpriteEntity([%d args]) = %p", n-1, this);
	for (int i = 2; i <= n; i++) {
		BitmapRef b = luabridge::Stack<BitmapRef>::get(l, i);
		bitmaps.push_back(b);
	}
}

SpriteEntity::~SpriteEntity() {
	// TODO Auto-generated destructor stub
}

void SpriteEntity::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
		.deriveClass<SpriteEntity, Entity>("SpriteEntity")
			.addConstructor<void(*)(), SpriteEntityRef>()
			//.addConstructor<void(*)(std::initializer_list<BitmapRef>)>()
			.addConstructor<void(*)(lua_State*), SpriteEntityRef>()
			.addFunction("addBitmap", &SpriteEntity::addBitmap)
			.addFunction("onTimer", &SpriteEntity::onTimer)
		.endClass()
	.endNamespace();
}

void SpriteEntity::onTimer(int tick) {
	frame++;
}

void SpriteEntity::addBitmap(BitmapRef bitmap) {
	bitmaps.push_back(bitmap);
}

void SpriteEntity::draw(GraphicsSurfaceRef s, int offx, int offy) {
	int numBitmaps = bitmaps.size();
	int frameID = frame % numBitmaps;
	s->drawBitmap(bitmaps[frameID], x - offx, y - offy);
}

int SpriteEntity::getW() const {
	if (bitmaps.size() == 0) {
		throw "Can't get width of SpriteEntity with no bitmaps";
	}

	return bitmaps[0]->getW();
}

int SpriteEntity::getH() const {
	if (bitmaps.size() == 0) {
		throw "Can't get height of SpriteEntity with no bitmaps";
	}

	return bitmaps[0]->getH();
}
