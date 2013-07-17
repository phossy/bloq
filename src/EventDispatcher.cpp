/*
 * EventDispatcher.cpp
 *
 *  Created on: Jul 17, 2013
 *      Author: jason
 */

#include "EventDispatcher.h"

LUA_REG_TYPE(EventDispatcher);

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
			.endClass()
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
	default:
		break;
	}
}

void EventDispatcher::addKeyListener(KeyListenerDelegate listener) {
	keyDelegates.push_back(listener);
}
