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

	static void __setRenderer(SDL_Renderer *r);

	friend class GraphicsSurface;
private:
	static SDL_Renderer *renderer;

	SDL_Texture *texture;
	int  w, h;
};

#endif /* BITMAP_H_ */
