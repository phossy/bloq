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

class SpriteEntity: public Entity, public ITimerCallback, LUA_DERIVED_CLASS(SpriteEntity) {
public:
	SpriteEntity();
	SpriteEntity(std::initializer_list<BitmapRef> bmps);
	virtual ~SpriteEntity();
	void addBitmap(BitmapRef bitmap);
	virtual void draw(GraphicsSurfaceRef s, int offx, int offy);
	virtual int getW() const;
	virtual int getH() const;

	static void registerLua(lua_State *l);
	//LUA_CLASS_GET_SHARED(Entity);
	//LUA_CLASS_GET_SHARED(SpriteEntity);
	
protected:
	virtual void onTimer(int tick);
	int frame;
	std::vector<BitmapRef> bitmaps;
};

//LUA_CLASS_SHARED_DEF(SpriteEntity);

#endif /* SPRITEENTITY_H_ */
