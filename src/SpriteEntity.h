/*
 * SpriteEntity.h
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#ifndef SPRITEENTITY_H_
#define SPRITEENTITY_H_

#include "Bitmap.h"
#include "Entity.h"
#include "ITimerCallback.h"
#include "ILuaClass.h"
#include <memory>
#include <vector>

class SpriteEntity;
typedef std::shared_ptr<SpriteEntity> SpriteEntityRef;

class SpriteEntity: public Entity, public ITimerCallback, public ILuaClass<SpriteEntity> {
public:
	SpriteEntity();
	SpriteEntity(std::initializer_list<BitmapRef> bmps);
	SpriteEntity(lua_State *l);
	virtual ~SpriteEntity();
	void addBitmap(BitmapRef bitmap);
	virtual void draw(GraphicsSurfaceRef s, int offx, int offy);
	virtual int getW() const;
	virtual int getH() const;

	static void registerLua(lua_State *l);
	
protected:
	virtual void onTimer(int tick);
	int frame;
	std::vector<BitmapRef> bitmaps;
};

LUA_MAKE_REF(SpriteEntity);

#endif /* SPRITEENTITY_H_ */
