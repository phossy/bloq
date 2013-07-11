/*
 * GraphicsSurface.h
 *
 *  Created on: Jul 10, 2013
 *      Author: jason
 */

#ifndef GRAPHICSSURFACE_H_
#define GRAPHICSSURFACE_H_

// forward declare due to circular references
class Bitmap;

#include <SDL2/SDL.h>
#include "Bitmap.h"

class GraphicsSurface {
public:
	GraphicsSurface();
	virtual ~GraphicsSurface();
	void drawBitmap(const Bitmap& bmp, int x, int y);

	int getW();
	int getH();

protected:
	virtual void repaint() = 0;
	virtual SDL_Surface* getSurface() = 0;
};

#endif /* GRAPHICSSURFACE_H_ */
