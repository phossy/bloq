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
#include "ILuaClass.h"

class Bitmap : public Asset, LUA_CLASS(Bitmap) {
public:
	Bitmap(const std::string& path);
	virtual ~Bitmap();

	int getW() const;
	int getH() const;

	using my_enable_shared_from_this<Bitmap>::shared_from_this;
	//inline std::shared_ptr<Bitmap> get_shared() { return shared_from_this(); }
	//LUA_CLASS_GET_SHARED_BASE(Bitmap, Asset);

	static void registerLua(lua_State *l);

	friend class GraphicsSurface;
private:
	SDL_Surface *surface;
};

namespace luabridge {
	template <> struct ContainerConstructionTraits<std::shared_ptr<Bitmap> > {
		static std::shared_ptr<Bitmap> constructContainer(Bitmap *t) {
			return t->shared_from_this();
		}
	};
}
//LUA_CLASS_SHARED_DEF(Bitmap);

#endif /* BITMAP_H_ */
