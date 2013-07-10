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

	renderWin = std::unique_ptr<RenderWindow>(new RenderWindow(config->get<int>("width"), config->get<int>("height"), config->get<bool>("fullscreen")));
}

Application::~Application() {
	Log::info("Shutting down");
	IMG_Quit();
	SDL_VideoQuit();
	SDL_Quit();
}

int Application::run() {
	// TODO test remove me!!!
	Bitmap b("assets/bog_green0.png");

	bool isStopping = false;
	while (!isStopping) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				Log::info("Quit event received");
				isStopping = true;
				break;
			default:
				//Log::info("Event: %d", e.type);
				break;
			}
		} else {
			sleep(1);
		}

		renderWin->drawBitmap(b, 100, 100);
		renderWin->repaint();
	}
	return 0;
}
