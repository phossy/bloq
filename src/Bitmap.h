/*
 * Bitmap.h
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include <memory>
class Bitmap;
typedef std::shared_ptr<Bitmap> BitmapRef;

#include "Asset.h"
#include "GraphicsSurface.h"
#include <SDL2/SDL.h>

class Bitmap : public Asset {
public:
	Bitmap(const std::string& path);
	virtual ~Bitmap();

	int getW();
	int getH();

	friend class GraphicsSurface;
private:
	SDL_Surface *surface;
};

#endif /* BITMAP_H_ */
