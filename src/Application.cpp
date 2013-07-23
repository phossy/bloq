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

Application::SDLInitializer::SDLInitializer() {
	// Basic SDL initialization
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	
	if (SDL_VideoInit(NULL) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		throw std::runtime_error(IMG_GetError());
	}
	
	if (TTF_Init() != 0) {
		throw std::runtime_error(TTF_GetError());
	}
	
	Log::info("SDL initialized");
}

Application::SDLInitializer::~SDLInitializer() {
	Log::info("SDL shutting down");
	
	// Shut down SDL
	TTF_Quit();
	IMG_Quit();
	SDL_VideoQuit();
	SDL_Quit();
}

Application::Application(int argc, char **argv) : args() {
	// Initialize SDL modules. This must be done first (and last),
	// because Lua destruction will be somewhat non-deterministic and
	// we can't risk calls to SDL being made from objects owned by scripts
	// after the library has been de-initialized
	sdl = std::make_shared<SDLInitializer>();
	
	// Lua script execution context
	scriptMgr = std::make_shared<ScriptManager>();
	
	// get the arguments
	for (int i = 0; i < argc; i++) {
		args.push_back(std::string(argv[i]));
	}

	// Initialize config
	config = std::make_shared<Config>();

	// render window
	renderWin = std::make_shared<RenderWindow>(
		config->get<int>("width"),
		config->get<int>("height"),
		config->get<bool>("fullscreen"));

	// Timer/looper
	timer = std::make_shared<Timer>();

	// Event dispatcher/handling
	eventDisp = std::make_shared<EventDispatcher>();

	// Game world object manager
	world = std::make_shared<World>();
	
	// Scripts console
	console = std::make_shared<Console>(scriptMgr);
	
	// register some lua game globals
	scriptMgr->addVar(DEFAULT_NAMESPACE, "world", world, false);
	scriptMgr->addVar(DEFAULT_NAMESPACE, "timer", timer, false);
	scriptMgr->addVar(DEFAULT_NAMESPACE, "event", eventDisp, false);
	scriptMgr->addVar(DEFAULT_NAMESPACE, "window", renderWin, false);
	scriptMgr->addVar(DEFAULT_NAMESPACE, "console", console, false);
	
	// Perform game initialization
	try {
		// TODO
		try {
			std::string scriptName = args.at(1);
			scriptMgr->runFile(scriptName);
		} catch (std::out_of_range const& e) {
			scriptMgr->runFile("assets/init.lua");
		}
	} catch (luabridge::LuaException const& e) {
		Log::warn("Script threw Lua exception: %s", e.what());
	} catch (std::exception const& e) {
		Log::warn("Script threw C++ exception: %s", e.what());
	} catch (...) {
		Log::warn("Script threw exception: unknown");
	}
	
	Log::info("Initialization completed");
}

Application::~Application() {
	Log::info("Shutting down");
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
	
#ifdef SHOW_FPS
	int lastTick = SDL_GetTicks();
	int repaints = 0;
#endif

	while (!isStopping) {
		SDL_Event e;

		// *** 1. Process events
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				Log::info("Quit event received");
				isStopping = true;
				break;
			default:
				if (console->isVisible()) { // as long as the console is visible it receives all input focus
					console->consumeEvent(e);
				} else {
					eventDisp->consumeEvent(e);
				}
				break;
			}
		}
		
		// *** 2. World updates
		// Collision detection
		world->checkAndNotifyCollidedEntities();
		
		// Remove entities queued for deletion
		world->drainRemovalQueue();
		
		// *** 3. Timer functions
		timer->tick();

		// *** 4. Redraw
		renderWin->drawRect(0, 0, renderWin->getW(), renderWin->getH(), COLOR_BLACK);
		world->drawArea(renderWin, renderWin->getViewX(), renderWin->getViewY());
		world->drawOverlays(renderWin);
		
		// Console display (on top of everything)
		console->draw(renderWin);
		
		renderWin->repaint();

#ifdef SHOW_FPS
		repaints++;

		if (SDL_GetTicks() - lastTick >= 1000) {
			Log::info("FPS = %d", repaints);
			repaints = 0;
			lastTick = SDL_GetTicks();
		}
#endif
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
