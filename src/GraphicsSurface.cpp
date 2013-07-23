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
RGBAColor COLOR_RED(255, 255, 0, 255);
RGBAColor COLOR_GREEN(0, 255, 0, 255);
RGBAColor COLOR_BLUE(0, 0, 255, 255);
RGBAColor COLOR_CYAN(0, 255, 255, 255);
RGBAColor COLOR_MAGENTA(255, 0, 255, 255);
RGBAColor COLOR_YELLOW(255, 255, 0, 255);
RGBAColor COLOR_GREY(127, 127, 127, 255);

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
				.addVariable("RED", &COLOR_RED, false)
				.addVariable("GREEN", &COLOR_GREEN, false)
				.addVariable("BLUE", &COLOR_BLUE, false)
				.addVariable("CYAN", &COLOR_CYAN, false)
				.addVariable("MAGENTA", &COLOR_MAGENTA, false)
				.addVariable("YELLOW", &COLOR_YELLOW, false)
				.addVariable("GREY", &COLOR_GREY, false)
			.endNamespace()
		.endNamespace();
}

void GraphicsSurface::drawBitmap(BitmapRef bmp, int x, int y) {
	SDL_Renderer *r = getRenderer();
	SDL_Rect rect = {x, y, bmp->getW(), bmp->getH()};

	SDL_RenderCopy(r, bmp->texture, NULL, &rect);
}

void GraphicsSurface::drawText(TypefaceRef font, int x, int y, const std::string& text, const RGBAColor& color) {
	if (text.length() == 0) {
		return; // nothing to do
	}
	
	SDL_Renderer *r = getRenderer();

	SDL_Surface *textSurf = TTF_RenderText_Blended(font->font, text.c_str(), MAKE_SDL_COLOR(color));
	if (textSurf == NULL) {
		throw std::runtime_error(TTF_GetError());
	}

	SDL_Rect rect = {x, y, textSurf->w, textSurf->h};

	SDL_Texture *texture = SDL_CreateTextureFromSurface(r, textSurf);
	SDL_FreeSurface(textSurf);
	if (texture == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
	SDL_RenderCopy(r, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

void GraphicsSurface::drawRect(int x, int y, int w, int h, const RGBAColor& color) {
	SDL_Renderer *r = getRenderer();
	SDL_Rect rect = {x, y, w, h};
	
	SDL_SetRenderDrawColor(r, std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color));
	SDL_RenderFillRect(r, &rect);
}
