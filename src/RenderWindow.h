/*
 * RenderWindow.h
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#ifndef RENDERWINDOW_H_
#define RENDERWINDOW_H_

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
	
	int getTargetFps() const;
	void setTargetFps(int fps);
	
	static void registerLua(lua_State *l);

	virtual int getW() const;
	virtual int getH() const;
protected:
	virtual SDL_Renderer* getRenderer() const;
private:
	int viewX, viewY, lastTimestamp, targetFps;
	
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif /* RENDERWINDOW_H_ */
