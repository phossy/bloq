/*
 * Bitmap.h
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include <memory>

class Bitmap;
typedef std::shared_ptr<Bitmap> BitmapRef;

#include "Asset.h"
#include "GraphicsSurface.h"
#include <SDL2/SDL.h>
#include "LuaClass.h"

class Bitmap : public Asset, public LuaClass<Bitmap> {
public:
	Bitmap(const std::string& path);
	virtual ~Bitmap();

	int getW() const;
	int getH() const;

	static void registerLua(lua_State *l);

	friend class GraphicsSurface;
private:
	SDL_Surface *surface;
};

#endif /* BITMAP_H_ */
