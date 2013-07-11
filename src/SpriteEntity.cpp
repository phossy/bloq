/*
 * SpriteEntity.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#include "SpriteEntity.h"
#include "Log.h"

SpriteEntity::SpriteEntity() : frame(0) {
}

SpriteEntity::~SpriteEntity() {
	// TODO Auto-generated destructor stub
}

void SpriteEntity::onTimer(int tick) {
	frame++;
}

void SpriteEntity::addBitmap(std::shared_ptr<Bitmap> bitmap) {
	bitmaps.push_back(bitmap);
}

void SpriteEntity::draw(GraphicsSurface& s) {
	int numBitmaps = bitmaps.size();
	int frameID = frame % numBitmaps;
	s.drawBitmap(*bitmaps[frameID], x, y);
}
