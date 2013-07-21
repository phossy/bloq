/*
 * GraphicsSurface.cpp
 *
 *  Created on: Jul 10, 2013
 *      Author: jason
 */

#include <stdexcept>
#include <SDL2/SDL_ttf.h>

#include "GraphicsSurface.h"

LUA_REG_TYPE(GraphicsSurface);

#define MAKE_SDL_COLOR(t) \
	SDL_Color{std::get<0>(t), std::get<1>(t), std::get<2>(t), std::get<3>(t)}

RGBAColor COLOR_BLACK(0, 0, 0, 255);
RGBAColor COLOR_WHITE(255, 255, 255, 255);

GraphicsSurface::GraphicsSurface() {
	// TODO Auto-generated constructor stub

}

GraphicsSurface::~GraphicsSurface() {
	// TODO Auto-generated destructor stub
}

void GraphicsSurface::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
			.beginClass<GraphicsSurface>("GraphicsSurface")
				.addProperty("w", &GraphicsSurface::getW)
				.addProperty("h", &GraphicsSurface::getH)
			.endClass()
			.beginNamespace(COLOR_NAMESPACE)
				.addVariable("BLACK", &COLOR_BLACK, false)
				.addVariable("WHITE", &COLOR_WHITE, false)
			.endNamespace()
		.endNamespace();
}

void GraphicsSurface::drawBitmap(BitmapRef bmp, int x, int y) {
	SDL_Surface *s = getSurface();

	SDL_Rect rect = {x, y, 0, 0};
	SDL_BlitSurface(bmp->surface, NULL, s, &rect);
}

void GraphicsSurface::drawText(TypefaceRef font, int x, int y, const std::string& text, const RGBAColor& color) {
	SDL_Surface *s = getSurface();
	SDL_Rect rect = {x, y, 0, 0};

	SDL_Surface *textSurf = TTF_RenderText_Blended(font->font, text.c_str(), MAKE_SDL_COLOR(color));
	if (textSurf == NULL) {
		throw std::runtime_error(TTF_GetError());
	}

	SDL_BlitSurface(textSurf, NULL, s, &rect);
}

int GraphicsSurface::getW() const {
	SDL_Surface *s = getSurface();
	return s->w;
}

int GraphicsSurface::getH() const {
	SDL_Surface *s = getSurface();
	return s->h;
}
