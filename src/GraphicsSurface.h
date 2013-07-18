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
#include <tuple>

class GraphicsSurface;
typedef std::shared_ptr<GraphicsSurface> GraphicsSurfaceRef;

#include "Bitmap.h"
#include "Typeface.h"

typedef std::tuple<unsigned char, unsigned char, unsigned char, unsigned char> RGBAColor;

// default colors
extern RGBAColor COLOR_BLACK;
extern RGBAColor COLOR_WHITE;

class GraphicsSurface {
public:
	GraphicsSurface();
	virtual ~GraphicsSurface();
	void drawBitmap(BitmapRef bmp, int x, int y);
	void drawText(TypefaceRef font, int x, int y, const std::string& text, const RGBAColor& color);

	int getW();
	int getH();

protected:
	virtual void repaint() = 0;
	virtual SDL_Surface* getSurface() = 0;
};

#endif /* GRAPHICSSURFACE_H_ */
