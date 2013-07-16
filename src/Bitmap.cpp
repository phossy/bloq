/*
 * Bitmap.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#include "Bitmap.h"
#include <SDL2/SDL_image.h>
#include "Log.h"

LUA_CLASS_REGISTER(Bitmap);

Bitmap::Bitmap(const std::string& path) : Asset(path) {
	Log::info("Bitmap::Bitmap(%s)", path.c_str());
	surface = IMG_Load_RW(file, 0);
	if (surface == NULL) {
		throw IMG_GetError();
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
				.addConstructor<void(*)(const std::string&)>()
				.addProperty("w", &Bitmap::getW)
				.addProperty("h", &Bitmap::getH)
			.endClass()
		.endNamespace();
}
