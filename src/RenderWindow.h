/*
 * RenderWindow.h
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#ifndef RENDERWINDOW_H_
#define RENDERWINDOW_H_

#define APPLICATION_NAME "APP NAME"

#include <SDL2/SDL.h>
#include <memory>

class RenderWindow;
typedef std::shared_ptr<RenderWindow> RenderWindowRef;

#include "LuaClass.h"
#include "GraphicsSurface.h"

class RenderWindow : public GraphicsSurface, public LuaClass<RenderWindow> {
public:
	RenderWindow(int w, int h, bool fullscreen);
	virtual ~RenderWindow();
	virtual void repaint();
	
	int getViewX() const;
	int getViewY() const;
	void setViewX(int x);
	void setViewY(int y);
	
	void setTargetFps(int fps);
	
	static void registerLua(lua_State *l);
protected:
	virtual SDL_Surface* getSurface() const;
private:
	int viewX, viewY, lastTimestamp, targetFps;
	
	SDL_Window* window;
	//SDL_Renderer* renderer;
};

#endif /* RENDERWINDOW_H_ */
