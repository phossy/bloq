/*
 * Bitmap.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#include "Bitmap.h"
#include <SDL2/SDL_image.h>

Bitmap::Bitmap(const std::string& path) : Asset(path) {
	surface = IMG_Load_RW(file, 0);
	if (surface == NULL) {
		throw IMG_GetError();
	}
}

Bitmap::~Bitmap() {
	SDL_FreeSurface(surface);
}

int Bitmap::getW() {
	return surface->w;
}

int Bitmap::getH() {
	return surface->h;
}
