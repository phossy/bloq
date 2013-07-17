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

int Application::run() {
	// TODO this can be structured differently
	ScriptManagerRef s = std::make_shared<ScriptManager>();
	WorldRef w = std::make_shared<World>();

	// Add global 'vars' to lua
	s->addVar(DEFAULT_NAMESPACE, "world", w, false);
	s->addVar(DEFAULT_NAMESPACE, "timer", timer, false);
	try {
		s->runFile("assets/init.lua");
	} catch (std::string &s) {
		Log::warn("Script threw exception: %s", s.c_str());
	}
	Log::info("Initialization script has finished");

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
