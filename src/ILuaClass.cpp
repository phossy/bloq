/*
 * ILuaClass.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: jason
 */
#include "ILuaClass.h"

std::list<LuaRegisterFunc>* ILuaClass::__regFuncs = nullptr;

ILuaClass::~ILuaClass() {
	delete __regFuncs;
}

void ILuaClass::__addRegFunc(LuaRegisterFunc f) {
	if (__regFuncs == nullptr) {
		__regFuncs = new std::list<LuaRegisterFunc>();
	}
	__regFuncs->push_back(f);
}

void ILuaClass::registerClasses(lua_State *l) {
	if (__regFuncs == nullptr) {
		return;
	}
	
	for (auto &func : *__regFuncs) {
		func(l);
	}
}
