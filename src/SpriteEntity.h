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
#include <memory>
#include <vector>

class SpriteEntity: public Entity, public ITimerCallback {
public:
	SpriteEntity();
	SpriteEntity(std::initializer_list<std::shared_ptr<Bitmap> > bmps);
	virtual ~SpriteEntity();
	void addBitmap(std::shared_ptr<Bitmap> bitmap);
	void draw(GraphicsSurface& s);

	virtual int getW();
	virtual int getH();

protected:
	virtual void onTimer(int tick);
	int frame;
	std::vector<std::shared_ptr<Bitmap> > bitmaps;
};

#endif /* SPRITEENTITY_H_ */
