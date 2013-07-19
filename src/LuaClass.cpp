/*
 * LuaClass.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: jason
 */
#include "LuaClass.h"

std::list<LuaRegisterFunc>* LuaClassImpl::__regFuncs = nullptr;

LuaClassImpl::~LuaClassImpl() {
	if (__regFuncs != nullptr) {
		delete __regFuncs;
		__regFuncs = nullptr;
	}
}

void LuaClassImpl::__addRegFunc(LuaRegisterFunc f) {
	if (__regFuncs == nullptr) {
		__regFuncs = new std::list<LuaRegisterFunc>();
	}
	__regFuncs->push_back(f);
}

void LuaClassImpl::__registerClasses(lua_State *l) {
	// TODO figure out a better solution to the lua casting hack
	// so that we don't need this
	luabridge::Security::setHideMetatables(false);
	
	if (__regFuncs == nullptr) {
		return;
	}
	
	for (auto &func : *__regFuncs) {
		func(l);
	}
}
