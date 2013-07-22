/*
 * Console.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: jason
 */

#include <stdexcept>
#include <utility>
#include <SDL2/SDL.h>

#include "Console.h"
#include "Log.h"

LUA_REG_TYPE(Console);

Console::Console(ScriptManagerRef script) : font(nullptr), visible(false), log(), curLine(""), maxLogLines(20) {
	scriptMgr = script;
}

Console::~Console() {
}

void Console::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
			.beginClass<Console>("Console")
				.addFunction("init", &Console::init)
				.addProperty("visible", &Console::isVisible, &Console::setVisible)
				.addFunction("print", &Console::print)
				.addFunction("clear", &Console::clear)
			.endClass()
		.endNamespace();
}

void Console::init(TypefaceRef f) {
	font = f;
}

void Console::draw(GraphicsSurfaceRef s) {
	if (visible) {
		int lineHeight = font->getLineHeight();
		
		// draw the prompt first
		s->drawRect(10, s->getH() - lineHeight - 10, s->getW() - 20, lineHeight, COLOR_BLACK);
		s->drawText(font, 10, s->getH() - lineHeight - 10, std::string(CONSOLE_PROMPT) + curLine, COLOR_GREEN);
		
		// draw the history
		int i = 2;
		for (auto &entry : log) {
			s->drawRect(10, s->getH() - (i * lineHeight) - 10, s->getW() - 20, lineHeight, COLOR_BLACK);
			s->drawText(font, 10, s->getH() - (i * lineHeight) - 10, entry.second, entry.first);
			++i;
		}
	}
}

void Console::consumeEvent(SDL_Event e) {
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_RETURN:
		case SDLK_RETURN2:
			// execute current line in buffer
			try {
				writeLine(COLOR_GREY, std::string(CONSOLE_PROMPT) + curLine);
				scriptMgr->runCode(curLine);
			} catch (luabridge::LuaException const& e) {
				Log::info("%s", e.what());
				writeLine(COLOR_YELLOW, std::string("Lua error: ") + std::string(e.what()));
			} catch (std::runtime_error const &e) {
				writeLine(COLOR_YELLOW, std::string("Exception: ") + std::string(e.what()));
			}
			curLine = "";
			break;
		case SDLK_BACKSPACE:
			if (curLine.length() > 0) {
				curLine.erase(curLine.end() - 1);
			}
			break;
		case SDLK_ESCAPE:
			// turn off console
			setVisible(false);
			break;
		}
		break;
	case SDL_TEXTINPUT:
		curLine += e.text.text;
		break;
	}
}

bool Console::isVisible() const {
	return visible;
}

void Console::setVisible(bool on) {
	if (font == nullptr) {
		return; // can't really activate the console until we have a font
	}
	visible = on;
	
	if (visible) {
		SDL_StartTextInput();
	} else {
		SDL_StopTextInput();
	}
}

void Console::print(const std::string& buf) {
	writeLine(COLOR_WHITE, buf);
}

void Console::clear() {
	log.clear();
}

void Console::writeLine(const RGBAColor& color, const std::string& buf) {
	log.push_front(std::make_pair(color, buf));
	while (log.size() > maxLogLines) {
		log.pop_back();
	}
}