/*
 * ScriptManager.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: jason
 */

#include <stdexcept>

#include "ScriptManager.h"

ScriptManager::ScriptManager() {
	state = luaL_newstate();
	// for debugging purposes
	luaJIT_setmode(state, 0, LUAJIT_MODE_ENGINE | LUAJIT_MODE_OFF);
	luaL_openlibs(state);
	
	//lua_sethook(state, &hookFunc, LUA_MASKLINE, 0);

	LuaClassImpl::__registerClasses(state);
}

ScriptManager::~ScriptManager() {
	lua_close(state);
	state = nullptr;
}

void ScriptManager::runCode(const std::string& code) {
	if (luaL_dostring(state, code.c_str()) != 0) {
		const std::string& err = luabridge::Stack<std::string const&>::get(state, -1);
		throw std::runtime_error(err);
	}
}

void ScriptManager::runFile(const std::string& file) {
	luaL_loadfile(state, file.c_str());
	luabridge::LuaRef r = luabridge::LuaRef::fromStack(state, 0);
	r();
	/*if (luaL_dofile(state, file.c_str()) != 0) {
		const std::string& err = luabridge::Stack<std::string const&>::get(state, -1);
		throw std::runtime_error(err);
	}*/
}

void ScriptManager::hookFunc(lua_State *l, lua_Debug *ar) {
	lua_getinfo(l, "S", ar);
	Log::info("lua execution trace: %s:%d", ar->short_src, ar->currentline);
}
