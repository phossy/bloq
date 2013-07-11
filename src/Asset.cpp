/*
 * Asset.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#include "Asset.h"

Asset::Asset(const std::string& path) {
	file = SDL_RWFromFile(path.c_str(), "r");
	if (file == NULL) {
		throw SDL_GetError();
	}
}

Asset::~Asset() {
	SDL_FreeRW(file);
}

