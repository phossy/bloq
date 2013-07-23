/*
 * Bitmap.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#include <SDL2/SDL_image.h>
#include <stdexcept>

#include "Bitmap.h"
#include "Log.h"

LUA_REG_TYPE(Bitmap);

SDL_Renderer* Bitmap::renderer = NULL;

Bitmap::Bitmap(const std::string& path) : Asset(path) {
	if (renderer == NULL) {
		throw std::logic_error("You must call Bitmap::__setRenderer() with a valid renderer");
	}

	Log::debug("Bitmap::Bitmap(%s) = %p", path.c_str(), this);
	SDL_Surface* surface = IMG_Load_RW(file, 0);
	if (surface == NULL) {
		throw std::runtime_error(IMG_GetError());
	}
	w = surface->w;
	h = surface->h;

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (texture == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
}

Bitmap::~Bitmap() {
	SDL_DestroyTexture(texture);
}

int Bitmap::getW() const {
	return w;
}

int Bitmap::getH() const {
	return h;
}

void Bitmap::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
			.deriveClass<Bitmap, Asset>("Bitmap")
				.addConstructor<void(*)(const std::string&), BitmapRef>()
				.addProperty("w", &Bitmap::getW)
				.addProperty("h", &Bitmap::getH)
			.endClass()
		.endNamespace();
}

void Bitmap::__setRenderer(SDL_Renderer *r) { // FIXME
	if (renderer != NULL) {
		throw std::logic_error("Can't call Bitmap::__setRenderer more than once");
	}
	renderer = r;
}

