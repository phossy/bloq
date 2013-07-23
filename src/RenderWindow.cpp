/*
 * RenderWindow.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#include <stdexcept>
#include <algorithm>

#include "RenderWindow.h"
#include "Bitmap.h"
#include "Log.h"

LUA_REG_TYPE(RenderWindow);

RenderWindow::RenderWindow(int w, int h, bool fullscreen) : viewX(0), viewY(0), targetFps(0) {
	// create the window and renderer
	if (SDL_CreateWindowAndRenderer(w, h, fullscreen ? SDL_WINDOW_FULLSCREEN : 0, &window, &renderer) < 0) {
		throw std::runtime_error(SDL_GetError());
	}
	
	SDL_RendererInfo info;
	if (SDL_GetRendererInfo(renderer, &info) < 0) {
		throw std::runtime_error(SDL_GetError());
	}

	Log::info("Using renderer: %s", info.name);
	Log::info("Max texture size: %d x %d", info.max_texture_width, info.max_texture_height);

	lastTimestamp = SDL_GetTicks();

	// FIXME - coupling that I do not like!
	Bitmap::__setRenderer(renderer);

	Log::info("RenderWindow initialized");
}

RenderWindow::~RenderWindow() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void RenderWindow::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
			.deriveClass<RenderWindow, GraphicsSurface>("RenderWindow")
				.addFunction("repaint", &RenderWindow::repaint)
				.addProperty("viewX", &RenderWindow::getViewX, &RenderWindow::setViewX)
				.addProperty("viewY", &RenderWindow::getViewY, &RenderWindow::setViewY)
				.addProperty("targetFps", &RenderWindow::getTargetFps, &RenderWindow::setTargetFps)
			.endClass()
	.endNamespace();
}

void RenderWindow::repaint() {
	SDL_RenderPresent(renderer);
	
	// FPS limiter
	if (targetFps != 0) {
		int delta = SDL_GetTicks() - lastTimestamp;
		SDL_Delay(std::max(0, (1000/targetFps) - delta));
		lastTimestamp = SDL_GetTicks();
	}
}

SDL_Renderer* RenderWindow::getRenderer() const {
	return renderer;
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

int RenderWindow::getTargetFps() const {
	return targetFps;
}

void RenderWindow::setTargetFps(int fps) {
	targetFps = fps;
}

int RenderWindow::getW() const {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	return w;
}

int RenderWindow::getH() const {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	return h;
}
