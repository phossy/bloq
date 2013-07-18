/*
 * Asset.h
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#ifndef ASSET_H_
#define ASSET_H_

#include <SDL2/SDL_rwops.h>
#include <string>
#include <memory>

class Asset;
typedef std::shared_ptr<Asset> AssetRef;

#include "LuaClass.h"

class Asset : public LuaClass<Asset> {
public:
	Asset(const std::string& path);
	virtual ~Asset();

	static void registerLua(lua_State *l);

protected:
	SDL_RWops *file;
};

#endif /* ASSET_H_ */
