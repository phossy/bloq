/*
 * EventDispatcher.cpp
 *
 *  Created on: Jul 17, 2013
 *      Author: jason
 */

#include "EventDispatcher.h"
#include <SDL2/SDL.h>

LUA_REG_TYPE(EventDispatcher);

static const int SDL_TO_INDEX_BUTTONS[] = {
	0,
	SDL_BUTTON_LEFT,	// 1
	SDL_BUTTON_RIGHT,	// 2
	SDL_BUTTON_MIDDLE,	// 3
	SDL_BUTTON_X1,		// 4
	SDL_BUTTON_X2		// 5
};

static int MOUSE_LEFT = 1;
static int MOUSE_RIGHT = 2;
static int MOUSE_MIDDLE = 3;
static int MOUSE_X1 = 4;
static int MOUSE_X2 = 5;

EventDispatcher::EventDispatcher() {
	// TODO Auto-generated constructor stub

}

EventDispatcher::~EventDispatcher() {
	// TODO Auto-generated destructor stub
}

void EventDispatcher::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
			.beginClass<EventDispatcher>("EventDispatcher")
				.addFunction("addKeyListener", &EventDispatcher::addKeyListener)
				.addFunction("addMouseButtonListener", &EventDispatcher::addMouseButtonListener)
				.addFunction("addMouseMotionListener", &EventDispatcher::addMouseMotionListener)
			.endClass()
			.beginNamespace(MOUSE_NAMESPACE)
				.addVariable("LEFT", &MOUSE_LEFT, false)
				.addVariable("RIGHT", &MOUSE_RIGHT, false)
				.addVariable("MIDDLE", &MOUSE_MIDDLE, false)
				.addVariable("X1", &MOUSE_X1, false)
				.addVariable("X2", &MOUSE_X2, false)
			.endNamespace()
	.endNamespace();
}

void EventDispatcher::consumeEvent(SDL_Event e) {
	switch (e.type) {
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		for (auto &d : keyDelegates) {
			std::string keyname(SDL_GetKeyName(e.key.keysym.sym));
			d(keyname, (e.key.state == SDL_PRESSED));
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		for (auto &d : mouseButtonDelegates) {
			d(SDL_TO_INDEX_BUTTONS[e.button.button], e.button.x, e.button.y, (e.button.state == SDL_PRESSED));
		}
		break;
	case SDL_MOUSEMOTION:
		for (auto &d : mouseMotionDelegates) {
			d(e.motion.x, e.motion.y);
		}
		break;
	default:
		break;
	}
}

void EventDispatcher::addKeyListener(KeyListenerDelegate listener) {
	keyDelegates.push_back(listener);
}

bool EventDispatcher::isKeyPressed(const std::string& key) {
	// TODO there is no bounds checking here. Fix this.
	SDL_Keycode keycode = SDL_GetKeyFromName(key.c_str());
	SDL_Scancode scancode = SDL_GetScancodeFromKey(keycode);
	const unsigned char* keys = SDL_GetKeyboardState(NULL);
	return keys[scancode];
}

void EventDispatcher::addMouseButtonListener(MouseButtonListenerDelegate listener) {
	mouseButtonDelegates.push_back(listener);
}

bool EventDispatcher::isMouseButtonPressed(int button) {
	return false; // TODO
}

void EventDispatcher::addMouseMotionListener(MouseMotionListenerDelegate listener) {
	mouseMotionDelegates.push_back(listener);
}
