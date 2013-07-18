/*
 * TextEntity.cpp
 *
 *  Created on: Jul 18, 2013
 *      Author: jason
 */

#include "TextEntity.h"

LUA_REG_TYPE(TextEntity);

TextEntity::TextEntity(TypefaceRef f) : font(f), text(), color(COLOR_WHITE), cachedBounds(std::make_pair(0, 0)) {
}

TextEntity::~TextEntity() {
	// TODO Auto-generated destructor stub
}

void TextEntity::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
			.deriveClass<TextEntity, Entity>("TextEntity")
				.addConstructor<void(*)(TypefaceRef), TextEntityRef>()
				.addProperty("text", &TextEntity::getString, &TextEntity::setString)
				.addProperty("color", &TextEntity::getColor, &TextEntity::setColor)
			.endClass()
		.endNamespace();
}

const std::string& TextEntity::getString() const {
	return text;
}

void TextEntity::setString(const std::string& t) {
	text = t;

	// recalculate the bounding box from the font
	cachedBounds = font->getTextBounds(text);
}

const RGBAColor& TextEntity::getColor() const {
	return color;
}

void TextEntity::setColor(const RGBAColor& c) {
	color = c;
}

void TextEntity::draw(GraphicsSurfaceRef s, int offx, int offy) {
	s->drawText(font, x, y, text, color);
}

int TextEntity::getW() const {
	return cachedBounds.first;
}

int TextEntity::getH() const {
	return cachedBounds.second;
}
