/*
 * ILuaClass.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: jason
 */
#include "ILuaClass.h"

std::list<LuaRegistrationFunc>* ILuaClass::__regFuncs = nullptr;

ILuaClass::~ILuaClass() {
	delete __regFuncs;
}

void ILuaClass::__addRegistrationFunc(LuaRegistrationFunc f) {
	if (__regFuncs == nullptr) {
		__regFuncs = new std::list<LuaRegistrationFunc>();
	}
	__regFuncs->push_back(f);
}
