/*
 * Typeface.h
 *
 *  Created on: Jul 18, 2013
 *      Author: jason
 */

#ifndef TYPEFACE_H_
#define TYPEFACE_H_

#include <memory>
#include <utility>
#include <string>
#include <SDL2/SDL_ttf.h>

class Typeface;
typedef std::shared_ptr<Typeface> TypefaceRef;

#include "LuaClass.h"
#include "Asset.h"
#include "GraphicsSurface.h"

class Typeface : public Asset, public LuaClass<Typeface> {
public:
	Typeface(const std::string& path, int pt);
	virtual ~Typeface();

	bool getBold() const;
	bool getItalic() const;
	bool getUnderline() const;
	bool getStrikethrough() const;

	void setBold(bool b);
	void setItalic(bool b);
	void setUnderline(bool b);
	void setStrikethrough(bool b);

	void clearStyles();

	std::pair<int, int> getTextBounds(const std::string& s);

	static void registerLua(lua_State *l);

	friend class GraphicsSurface;
private:
	TTF_Font *font;
};

#endif /* TYPEFACE_H_ */
