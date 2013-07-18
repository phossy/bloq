/*
 * Application.h
 *
 *  Created on: Jul 8, 2013
 *      Author: jason
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <memory>

class Application;
typedef std::shared_ptr<Application> ApplicationRef;

#include "LuaClass.h"
#include "RenderWindow.h"
#include "Config.h"
#include "Timer.h"
#include "ScriptManager.h"
#include "World.h"
#include "EventDispatcher.h"

#define TICK 100

class Application {
public:
	Application(int argc, char **argv);
	virtual ~Application();
	int run();
	
	static void quit();
	
	static void registerLua(lua_State *l);
private:
	RenderWindowRef renderWin;
	ConfigRef config;
	TimerRef timer;
	ScriptManagerRef scriptMgr;
	WorldRef world;
	EventDispatcherRef eventDisp;
};

#endif /* APPLICATION_H_ */
