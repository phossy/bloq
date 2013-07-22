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
	destroy();
}

void ScriptManager::destroy() {
	if (state != nullptr) {
		lua_close(state);
		state = nullptr;
	}
}

void ScriptManager::runCode(const std::string& code) {
	luaL_loadstring(state, code.c_str());
	luaCall();
	//luaL_dostring(state, code.c_str());
}

void ScriptManager::runFile(const std::string& file) {
	luaL_loadfile(state, file.c_str());
	luaCall();
}

void ScriptManager::luaCall() {
	if (state == nullptr) {
		throw std::logic_error("The lua context is destroyed");
	}
	
	// call whatever is on the top of the stack
	luabridge::LuaRef f = luabridge::LuaRef::fromStack(state, lua_gettop(state));
	f();
}

void ScriptManager::hookFunc(lua_State *l, lua_Debug *ar) {
	lua_getinfo(l, "S", ar);
	Log::info("lua execution trace: %s:%d", ar->short_src, ar->currentline);
}
