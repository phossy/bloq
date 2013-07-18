/*
 * Asset.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#include <stdexcept>

#include "Asset.h"
#include "Log.h"

LUA_REG_TYPE(Asset);

Asset::Asset(const std::string& path) {
	file = SDL_RWFromFile(path.c_str(), "r");
	if (file == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
}

Asset::~Asset() {
	SDL_FreeRW(file);
}

void Asset::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
			.beginClass<Asset>("Asset")
				.addConstructor<void(*)(const std::string&), AssetRef>()
			.endClass()
		.endNamespace();
}

