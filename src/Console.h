/*
 * Console.h
 *
 *  Created on: Jul 21, 2013
 *      Author: jason
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <SDL2/SDL_rwops.h>
#include <string>
#include <deque>
#include <memory>

class Console;
typedef std::shared_ptr<Console> ConsoleRef;

#include "LuaClass.h"
#include "ScriptManager.h"
#include "Typeface.h"

#define CONSOLE_PROMPT "> "

class Console : public LuaClass<Console> {
public:
	Console(ScriptManagerRef script);
	virtual ~Console();
	
	void init(TypefaceRef f);
	void draw(GraphicsSurfaceRef s);
	
	void consumeEvent(SDL_Event e);
	
	bool isVisible() const;
	void setVisible(bool on);

	static void registerLua(lua_State *l);
	
	void print(const std::string& buf); // convenience function to access from scripts
	void clear();
	
	void writeLine(const RGBAColor& color, const std::string& buf);
	
private:
	TypefaceRef font;
	bool visible;
	ScriptManagerRef scriptMgr;
	
	std::deque<std::pair<RGBAColor, std::string> > log;
	std::string curLine;
	
	int maxLogLines;
};

#endif /* CONSOLE_H_ */
