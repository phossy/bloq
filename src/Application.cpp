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

Application::Application(int argc, char **argv) {
	// TODO argument parsing

	// Initialize config
	config = std::make_shared<Config>();

	// Basic SDL initialization
	Log::info("Initializing SDL");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		throw SDL_GetError();
	}

	Log::info("Initializing SDL video subsystem");
	if (SDL_VideoInit(NULL) != 0) {
		throw SDL_GetError();
	}

	Log::info("Initializing SDL_image");
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		throw IMG_GetError();
	}

	// render window
	renderWin = std::make_shared<RenderWindow>(config->get<int>("width"), config->get<int>("height"), config->get<bool>("fullscreen"));

	// event timer/looper
	timer = std::make_shared<Timer>();
}

Application::~Application() {
	Log::info("Shutting down");
	IMG_Quit();
	SDL_VideoQuit();
	SDL_Quit();
}

namespace luabridge {
	
	template <> struct ArgList<void*> {
		ArgList<void*>(lua_State *l) {}
	};
	
	template <> struct FuncTraits<std::function<WorldRef()>* > {
		typedef WorldRef ReturnType;
		typedef void* Params;
		static ReturnType call(std::function<WorldRef()>* fnptr, ArgList<Params> args) {
			Log::info("func func func!");
			return (*fnptr)();
		}
	};
}

int Application::run() {
	// TODO more tests with lua, get rid of me
	ScriptManagerRef s = std::make_shared<ScriptManager>();

	// TODO test remove me!!!
	WorldRef w = std::make_shared<World>();
	//World w;
	EntityPrototype entPrototype = [&]() {
		auto ent = std::shared_ptr<SpriteEntity>(
												 new SpriteEntity{
													 std::make_shared<Bitmap>("assets/PlanetCute PNG/Plain Block.png"),
													 std::make_shared<Bitmap>("assets/PlanetCute PNG/Stone Block.png")
												 });
		timer->schedule(*ent, 5);
		return ent;
	};
	w->getEntityFactory()->registerPrototype("test", entPrototype);

	//luabridge::LuaRef v (l, &w);
	//std::function<WorldRef()> func = [&w]() -> WorldRef { return w; };
	
	s->runFile("assets/init.lua");
	
	//w.spawnEntityAt("test", 100, 100);

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
				break;
			}
		}

		// Tick the timer to let callbacks fire
		timer->tick();

		// Redraw
		w->drawArea(renderWin, 0, 0);
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
