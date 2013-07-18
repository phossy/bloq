/*
 * GraphicsSurface.h
 *
 *  Created on: Jul 10, 2013
 *      Author: jason
 */

#ifndef GRAPHICSSURFACE_H_
#define GRAPHICSSURFACE_H_

#include <SDL2/SDL.h>
#include <memory>

class GraphicsSurface;
typedef std::shared_ptr<GraphicsSurface> GraphicsSurfaceRef;

#include "Bitmap.h"

class GraphicsSurface {
public:
	GraphicsSurface();
	virtual ~GraphicsSurface();
	void drawBitmap(BitmapRef bmp, int x, int y);

	int getW();
	int getH();

protected:
	virtual void repaint() = 0;
	virtual SDL_Surface* getSurface() = 0;
};

#endif /* GRAPHICSSURFACE_H_ */
