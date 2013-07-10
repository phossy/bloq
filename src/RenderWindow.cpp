/*
 * RenderWindow.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#include "RenderWindow.h"
#include "Log.h"

RenderWindow::RenderWindow(int w, int h, bool fullscreen) {
	// create the window
	window = SDL_CreateWindow(APPLICATION_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
	if (window == NULL) {
		throw SDL_GetError();
	}

	// create the renderer
	/*renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		throw SDL_GetError();
	}*/

	Log::info("RenderWindow initialized");
}

RenderWindow::~RenderWindow() {
	//SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void RenderWindow::repaint() {
	SDL_UpdateWindowSurface(window);
}

SDL_Surface* RenderWindow::getSurface() {
	return SDL_GetWindowSurface(window);
}
