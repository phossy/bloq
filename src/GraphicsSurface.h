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

#include "LuaClass.h"
#include "Bitmap.h"
#include "Typeface.h"

typedef std::tuple<unsigned char, unsigned char, unsigned char, unsigned char> RGBAColor;

// default colors
extern RGBAColor COLOR_BLACK;
extern RGBAColor COLOR_WHITE;

class GraphicsSurface : public LuaClass<GraphicsSurface> {
public:
	GraphicsSurface();
	virtual ~GraphicsSurface();
	void drawBitmap(BitmapRef bmp, int x, int y);
	void drawText(TypefaceRef font, int x, int y, const std::string& text, const RGBAColor& color);
	void drawRect(int x, int y, int w, int h, const RGBAColor& color);

	int getW() const;
	int getH() const;
	
	static void registerLua(lua_State *l);
protected:
	virtual void repaint() = 0;
	virtual SDL_Surface* getSurface() const = 0;
};

#endif /* GRAPHICSSURFACE_H_ */
