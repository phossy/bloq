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
}

Bitmap::~Bitmap() {
	SDL_FreeSurface(surface);
}

