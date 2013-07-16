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
#include "ILuaClass.h"

class Asset;
typedef std::shared_ptr<Asset> AssetRef;

class Asset : LUA_CLASS(Asset) {
public:
	Asset(const std::string& path);
	virtual ~Asset();

	static void registerLua(lua_State *l);
	using my_enable_shared_from_this<Asset>::shared_from_this;
	inline std::shared_ptr<Asset> get_shared() { return shared_from_this(); }
	//LUA_CLASS_GET_SHARED(Asset);

protected:
	SDL_RWops *file;
};

LUA_CLASS_SHARED_DEF(Asset);

#endif /* ASSET_H_ */
