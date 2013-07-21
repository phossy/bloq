/*
 * Typeface.cpp
 *
 *  Created on: Jul 18, 2013
 *      Author: jason
 */

#include <stdexcept>
#include "Typeface.h"

LUA_REG_TYPE(Typeface);

Typeface::Typeface(const std::string& path, int pt) : Asset(path) {
	font = TTF_OpenFontRW(file, 0, pt);
	if (font == NULL) {
		throw std::runtime_error(TTF_GetError());
	}
}

Typeface::~Typeface() {
	// just in case SDL_ttf is shut down before we get here
	if (TTF_WasInit()) {
		TTF_CloseFont(font);
	}
}

void Typeface::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
			.deriveClass<Typeface, Asset>("Typeface")
				.addConstructor<void(*)(const std::string&, int), TypefaceRef>()
				.addProperty("bold", &Typeface::getBold, &Typeface::setBold)
				.addProperty("italic", &Typeface::getItalic, &Typeface::setItalic)
				.addProperty("underline", &Typeface::getUnderline, &Typeface::setUnderline)
				.addProperty("strikethrough", &Typeface::getStrikethrough, &Typeface::setStrikethrough)
				.addFunction("clearStyles", &Typeface::clearStyles)
				.addFunction("getTextBounds", &Typeface::getTextBounds)
			.endClass()
		.endNamespace();
}

bool Typeface::getBold() const {
	return TTF_GetFontStyle(font) & TTF_STYLE_BOLD;
}

bool Typeface::getItalic() const {
	return TTF_GetFontStyle(font) & TTF_STYLE_ITALIC;
}

bool Typeface::getUnderline() const {
	return TTF_GetFontStyle(font) & TTF_STYLE_UNDERLINE;
}

bool Typeface::getStrikethrough() const {
	return TTF_GetFontStyle(font) & TTF_STYLE_STRIKETHROUGH;
}

void Typeface::setBold(bool b) {
	int style = TTF_GetFontStyle(font);
	if (b != (style & TTF_STYLE_BOLD)) { // avoid flushing the glyph cache
		if (b) {
			TTF_SetFontStyle(font, style | TTF_STYLE_BOLD);
		} else {
			TTF_SetFontStyle(font, style & ~TTF_STYLE_BOLD);
		}
	}
}

void Typeface::setItalic(bool b) {
	int style = TTF_GetFontStyle(font);
	if (b != (style & TTF_STYLE_ITALIC)) { // avoid flushing the glyph cache
		if (b) {
			TTF_SetFontStyle(font, style | TTF_STYLE_ITALIC);
		} else {
			TTF_SetFontStyle(font, style & ~TTF_STYLE_ITALIC);
		}
	}
}

void Typeface::setUnderline(bool b) {
	int style = TTF_GetFontStyle(font);
	if (b != (style & TTF_STYLE_UNDERLINE)) { // avoid flushing the glyph cache
		if (b) {
			TTF_SetFontStyle(font, style | TTF_STYLE_UNDERLINE);
		} else {
			TTF_SetFontStyle(font, style & ~TTF_STYLE_UNDERLINE);
		}
	}
}

void Typeface::setStrikethrough(bool b) {
	int style = TTF_GetFontStyle(font);
	if (b != (style & TTF_STYLE_STRIKETHROUGH)) { // avoid flushing the glyph cache
		if (b) {
			TTF_SetFontStyle(font, style | TTF_STYLE_STRIKETHROUGH);
		} else {
			TTF_SetFontStyle(font, style & ~TTF_STYLE_STRIKETHROUGH);
		}
	}
}

void Typeface::clearStyles() {
	int style = TTF_GetFontStyle(font);
	if (style != 0) { // avoid flushing the glyph cache
		TTF_SetFontStyle(font, 0);
	}
}

std::pair<int, int> Typeface::getTextBounds(const std::string& s) {
	int w, h;
	if (TTF_SizeUTF8(font, s.c_str(), &w, &h) == -1) {
		throw std::runtime_error(TTF_GetError());
	}
	return std::make_pair(w, h);
}
