/*
 * RenderWindow.h
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#ifndef RENDERWINDOW_H_
#define RENDERWINDOW_H_

#define APPLICATION_NAME "APP NAME"

#include "GraphicsSurface.h"
#include <SDL2/SDL.h>
#include <memory>

class RenderWindow;
typedef std::shared_ptr<RenderWindow> RenderWindowRef;

class RenderWindow : public GraphicsSurface {
public:
	RenderWindow(int w, int h, bool fullscreen);
	virtual ~RenderWindow();
	virtual void repaint();

protected:
	virtual SDL_Surface* getSurface();
private:
	SDL_Window* window;
	//SDL_Renderer* renderer;
};

#endif /* RENDERWINDOW_H_ */
