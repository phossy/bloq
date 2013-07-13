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

Application::Application(int argc, char **argv) {
	// TODO argument parsing

	// Initialize config
	config = std::unique_ptr<Config>(new Config());

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
	renderWin = std::unique_ptr<RenderWindow>(new RenderWindow(config->get<int>("width"), config->get<int>("height"), config->get<bool>("fullscreen")));

	// event timer/looper
	timer = std::unique_ptr<Timer>(new Timer());
}

Application::~Application() {
	Log::info("Shutting down");
	IMG_Quit();
	SDL_VideoQuit();
	SDL_Quit();
}

int Application::run() {
	// TODO test remove me!!!
	World w;
	EntityPrototype entPrototype = [&]() {
		auto ent = std::shared_ptr<SpriteEntity>(
												 new SpriteEntity{
													 std::make_shared<Bitmap>("assets/PlanetCute PNG/Plain Block.png"),
													 std::make_shared<Bitmap>("assets/PlanetCute PNG/Stone Block.png")
												 });
		timer->schedule(*ent, 5);
		return ent;
	};
	w.getEntityFactory().registerPrototype("test", entPrototype);
	w.spawnEntityAt("test", 100, 100);

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
		w.drawArea(*renderWin, 0, 0);
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
