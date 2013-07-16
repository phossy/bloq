/*
 * ILuaClass.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: jason
 */
#include "ILuaClass.h"

std::list<LuaRegisterFunc>* ILuaClassImpl::__regFuncs = nullptr;

ILuaClassImpl::~ILuaClassImpl() {
	if (__regFuncs != nullptr) {
		delete __regFuncs;
		__regFuncs = nullptr;
	}
}

void ILuaClassImpl::__addRegFunc(LuaRegisterFunc f) {
	if (__regFuncs == nullptr) {
		__regFuncs = new std::list<LuaRegisterFunc>();
	}
	__regFuncs->push_back(f);
}

void ILuaClassImpl::__registerClasses(lua_State *l) {
	if (__regFuncs == nullptr) {
		return;
	}
	
	for (auto &func : *__regFuncs) {
		func(l);
	}
}
