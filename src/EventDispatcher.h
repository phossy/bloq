/*
 * EventDispatcher.h
 *
 *  Created on: Jul 17, 2013
 *      Author: jason
 */

#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

class EventDispatcher;
typedef std::shared_ptr<EventDispatcher> EventDispatcherRef;

#include "LuaClass.h"

typedef std::function<void(const std::string& keyName, bool pressed)> KeyListenerDelegate;
typedef std::function<void(int buttonIndex, int x, int y, bool pressed)> MouseButtonListenerDelegate;
typedef std::function<void(int x, int y)> MouseMotionListenerDelegate;

class EventDispatcher : public LuaClass<EventDispatcher> {
public:
	EventDispatcher();
	virtual ~EventDispatcher();

	void consumeEvent(SDL_Event e);

	void addKeyListener(KeyListenerDelegate listener);
	bool isKeyPressed(const std::string& key);
	
	void addMouseButtonListener(MouseButtonListenerDelegate listener);
	bool isMouseButtonPressed(int button);
	
	void addMouseMotionListener(MouseMotionListenerDelegate listener);
	
	static void registerLua(lua_State *l);

private:
	std::vector<KeyListenerDelegate> keyDelegates;
	std::vector<MouseButtonListenerDelegate> mouseButtonDelegates;
	std::vector<MouseMotionListenerDelegate> mouseMotionDelegates;
};

#endif /* EVENTDISPATCHER_H_ */
