/*
 * GraphicsSurface.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: jason
 */

#include "GraphicsSurface.h"

GraphicsSurface::GraphicsSurface() {
	// TODO Auto-generated constructor stub

}

GraphicsSurface::~GraphicsSurface() {
	// TODO Auto-generated destructor stub
}

void GraphicsSurface::drawBitmap(const Bitmap& bmp, int x, int y) {
	SDL_Surface *s = getSurface();

	SDL_Rect rect = {x, y, 0, 0};
	SDL_BlitSurface(bmp.surface, NULL, s, &rect);
}
