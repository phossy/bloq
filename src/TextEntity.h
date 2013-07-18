/*
 * TextEntity.h
 *
 *  Created on: Jul 18, 2013
 *      Author: jason
 */

#ifndef TEXTENTITY_H_
#define TEXTENTITY_H_

#include <memory>
#include <string>
#include <utility>

class TextEntity;
typedef std::shared_ptr<TextEntity> TextEntityRef;

#include "LuaClass.h"
#include "Entity.h"
#include "Typeface.h"
#include "GraphicsSurface.h"

class TextEntity: public Entity, public LuaClass<TextEntity> {
public:
	TextEntity(TypefaceRef f);
	virtual ~TextEntity();

	const std::string& getString() const;
	void setString(const std::string& t);
	const RGBAColor& getColor() const;
	void setColor(const RGBAColor& c);

	virtual void draw(GraphicsSurfaceRef s, int offx, int offy);
	virtual int getW() const;
	virtual int getH() const;

	static void registerLua(lua_State *l);

private:
	TypefaceRef font;
	std::string text;
	RGBAColor color;

	std::pair<int, int> cachedBounds;
};

#endif /* TEXTENTITY_H_ */
