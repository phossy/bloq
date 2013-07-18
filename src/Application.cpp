/*
 * Application.cpp
 *
 *  Created on: Jul 8, 2013
 *      Author: jason
 */

#include "Application.h"
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Log.h"
#include <unistd.h>

#include "SpriteEntity.h"
#include "World.h"
#include "ScriptManager.h"

#include <luajit-2.0/lua.hpp>
#include <LuaBridge/LuaBridge.h>

LUA_REG_TYPE(Application);

Application::Application(int argc, char **argv) {
	// TODO argument parsing

	// Initialize config
	config = std::make_shared<Config>();

	// Basic SDL initialization
	Log::info("Initializing SDL");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		throw std::runtime_error(SDL_GetError());
	}

	Log::info("Initializing SDL video subsystem");
	if (SDL_VideoInit(NULL) != 0) {
		throw std::runtime_error(SDL_GetError());
	}

	Log::info("Initializing SDL_image");
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		throw std::runtime_error(IMG_GetError());
	}

	Log::info("Initializing SDL_ttf");
	if (TTF_Init() != 0) {
		throw std::runtime_error(TTF_GetError());
	}

	// render window
	renderWin = std::make_shared<RenderWindow>(config->get<int>("width"), config->get<int>("height"), config->get<bool>("fullscreen"));

	// Timer/looper
	timer = std::make_shared<Timer>();

	// Event dispatcher/handling
	eventDisp = std::make_shared<EventDispatcher>();

	// Game world object manager
	world = std::make_shared<World>();

	// Lua script execution context
	scriptMgr = std::make_shared<ScriptManager>();

	// register some lua game globals
	scriptMgr->addVar(DEFAULT_NAMESPACE, "world", world, false);
	scriptMgr->addVar(DEFAULT_NAMESPACE, "timer", timer, false);
	scriptMgr->addVar(DEFAULT_NAMESPACE, "event", eventDisp, false);

	// Perform game initialization
	try {
		// TODO
		scriptMgr->runFile("assets/init.lua");
	} catch (luabridge::LuaException const& e) {
		Log::warn("Script threw LuaException: %s", e.what());
	} catch (std::exception const& e) {
		Log::warn("Script threw exception: %s", e.what());
	} catch (...) {
		Log::warn("Script threw exception");
	}

	Log::info("Initialization completed");
}

Application::~Application() {
	Log::info("Shutting down");
	TTF_Quit();
	IMG_Quit();
	SDL_VideoQuit();
	SDL_Quit();
}

void Application::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
			.addFunction("quit", &Application::quit)
	.endNamespace();
}

int Application::run() {
	// ---------- MAIN LOOP ----------
	bool isStopping = false;
	while (!isStopping) {
		int beginMs = SDL_GetTicks();

		SDL_Event e;

		// retrieve waiting events
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				Log::info("Quit event received");
				isStopping = true;
				break;
			default:
				eventDisp->consumeEvent(e);
				break;
			}
		}

		// Tick the timer to let callbacks fire
		timer->tick();

		// Redraw
		world->drawArea(renderWin, 0, 0);
		renderWin->repaint();

		int delta = SDL_GetTicks() - beginMs;
		// wait if there is still time left this tick
		if (delta < TICK) {
			SDL_Delay(TICK - delta);
		} else if (delta > TICK) {
			Log::info("Event loop slowdown: %d ms behind", delta - TICK);
		}
	}

	// ----------
	return 0;
}

void Application::quit() {
	// Manually push a quit event into the queue to make the run loop exit
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}
