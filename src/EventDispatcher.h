/*
 * EventDispatcher.h
 *
 *  Created on: Jul 17, 2013
 *      Author: jason
 */

#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include "LuaClass.h"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

class EventDispatcher;
typedef std::shared_ptr<EventDispatcher> EventDispatcherRef;

typedef std::function<void(std::string&, bool)> KeyListenerDelegate;

class EventDispatcher : public LuaClass<EventDispatcher> {
public:
	EventDispatcher();
	virtual ~EventDispatcher();

	void consumeEvent(SDL_Event e);

	void addKeyListener(KeyListenerDelegate listener);

	static void registerLua(lua_State *l);

private:
	std::vector<KeyListenerDelegate> keyDelegates;
};

#endif /* EVENTDISPATCHER_H_ */
