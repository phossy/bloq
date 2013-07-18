/*
 * SpriteEntity.h
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#ifndef SPRITEENTITY_H_
#define SPRITEENTITY_H_

#include <memory>
#include <vector>

class SpriteEntity;
typedef std::shared_ptr<SpriteEntity> SpriteEntityRef;

#include "Bitmap.h"
#include "Entity.h"
#include "LuaClass.h"

class SpriteEntity: public Entity, public LuaClass<SpriteEntity> {
public:
	SpriteEntity();
	SpriteEntity(std::initializer_list<BitmapRef> bmps);
	SpriteEntity(lua_State *l);
	virtual ~SpriteEntity();
	void addBitmap(BitmapRef bitmap);
	virtual void draw(GraphicsSurfaceRef s, int offx, int offy);
	virtual int getW() const;
	virtual int getH() const;
	
	void onTimer(int tick);

	static void registerLua(lua_State *l);
	
protected:
	int frame;
	std::vector<BitmapRef> bitmaps;
};

#endif /* SPRITEENTITY_H_ */
