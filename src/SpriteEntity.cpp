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

SpriteEntity::SpriteEntity(std::initializer_list<std::shared_ptr<Bitmap> > bmps) : frame(0), bitmaps(bmps) {
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

void SpriteEntity::draw(GraphicsSurface& s, int offx, int offy) {
	int numBitmaps = bitmaps.size();
	int frameID = frame % numBitmaps;
	s.drawBitmap(*bitmaps[frameID], x - offx, y - offy);
}

int SpriteEntity::getW() {
	if (bitmaps.size() == 0) {
		throw "Can't get width of SpriteEntity with no bitmaps";
	}

	return bitmaps[0]->getW();
}

int SpriteEntity::getH() {
	if (bitmaps.size() == 0) {
		throw "Can't get height of SpriteEntity with no bitmaps";
	}

	return bitmaps[0]->getH();
}
