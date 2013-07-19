/*
 * Application.h
 *
 *  Created on: Jul 8, 2013
 *      Author: jason
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <memory>
#include <vector>
#include <string>

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
	
	std::vector<std::string> args;
	
	// This is in its own class as we need to be careful about the destruction order
	// so that all references to objects get released and resources deleted before
	// shutting down libraries such as freetype
	class SDLInitializer {
	public:
		SDLInitializer();
		virtual ~SDLInitializer();
	};
	typedef std::shared_ptr<SDLInitializer> SDLInitializerRef;
	SDLInitializerRef sdl;
};

#endif /* APPLICATION_H_ */
