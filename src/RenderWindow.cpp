/*
 * RenderWindow.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#include <stdexcept>
#include <algorithm>

#include "RenderWindow.h"
#include "Log.h"

LUA_REG_TYPE(RenderWindow);

RenderWindow::RenderWindow(int w, int h, bool fullscreen) : viewX(0), viewY(0), targetFps(0) {
	// create the window
	window = SDL_CreateWindow(APPLICATION_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
	if (window == NULL) {
		throw std::runtime_error(SDL_GetError());
	}

	// create the renderer
	/*renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		throw std::runtime_error(SDL_GetError());
	}*/
	
	lastTimestamp = SDL_GetTicks();

	Log::info("RenderWindow initialized");
}

RenderWindow::~RenderWindow() {
	//SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void RenderWindow::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
			.deriveClass<RenderWindow, GraphicsSurface>("RenderWindow")
				.addFunction("repaint", &RenderWindow::repaint)
				.addProperty("viewX", &RenderWindow::getViewX, &RenderWindow::setViewX)
				.addProperty("viewY", &RenderWindow::getViewY, &RenderWindow::setViewY)
				.addFunction("setTargetFps", &RenderWindow::setTargetFps)
			.endClass()
	.endNamespace();
}

void RenderWindow::repaint() {
	SDL_UpdateWindowSurface(window);
	
	// FPS limiter
	if (targetFps != 0) {
		int delta = SDL_GetTicks() - lastTimestamp;
		SDL_Delay(std::max(0, (1000/targetFps) - delta));
		lastTimestamp = SDL_GetTicks();
	}
}

SDL_Surface* RenderWindow::getSurface() const {
	return SDL_GetWindowSurface(window);
}

int RenderWindow::getViewX() const {
	return viewX;
}

int RenderWindow::getViewY() const {
	return viewY;
}

void RenderWindow::setViewX(int x) {
	viewX = x;
}

void RenderWindow::setViewY(int y) {
	viewY = y;
}

void RenderWindow::setTargetFps(int fps) {
	targetFps = fps;
}
