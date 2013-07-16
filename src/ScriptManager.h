/*
 * ScriptManager.h
 *
 *  Created on: Jul 15, 2013
 *      Author: jason
 */

#ifndef SCRIPTMANAGER_H_
#define SCRIPTMANAGER_H_

#include <string>

#include <luajit-2.0/lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include "ILuaClass.h"

class ScriptManager;
typedef std::shared_ptr<ScriptManager> ScriptManagerRef;

class ScriptManager {
public:
	ScriptManager();
	virtual ~ScriptManager();
	
	void runCode(const std::string& code);
	void runFile(const std::string& file); // TODO use Asset
private:
	lua_State* state;
};

#endif /* SCRIPTMANAGER_H_ */
