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

class ScriptManager;
typedef std::shared_ptr<ScriptManager> ScriptManagerRef;

#include "LuaClass.h"

class ScriptManager {
public:
	ScriptManager();
	virtual ~ScriptManager();
	
	void runCode(const std::string& code);
	void runFile(const std::string& file); // TODO use Asset

	template <class T> void addVar(const std::string& ns, const std::string& varname, T& var, bool rw = true) {
		luabridge::getGlobalNamespace(state)
			.beginNamespace(ns.c_str())
				.addVariable(varname.c_str(), &var, rw)
			.endNamespace();
	}

	static void hookFunc(lua_State *l, lua_Debug *ar);

private:
	lua_State* state;
};

#endif /* SCRIPTMANAGER_H_ */
