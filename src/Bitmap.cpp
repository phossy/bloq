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

Bitmap::Bitmap(const std::string& path) : Asset(path) {
	Log::debug("Bitmap::Bitmap(%s) = %p", path.c_str(), this);
	surface = IMG_Load_RW(file, 0);
	if (surface == NULL) {
		throw std::runtime_error(IMG_GetError());
	}
}

Bitmap::~Bitmap() {
	SDL_FreeSurface(surface);
}

int Bitmap::getW() const {
	return surface->w;
}

int Bitmap::getH() const {
	return surface->h;
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
