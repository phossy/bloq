/*
 * Timer.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#include "Timer.h"

LUA_REG_TYPE(Timer);

Timer::Timer() : curTick(0) {
}

Timer::~Timer() {

}

void Timer::registerLua(lua_State *l) {
	luabridge::getGlobalNamespace(l)
		.beginNamespace(DEFAULT_NAMESPACE)
			.beginClass<Timer>("Timer")
				.addFunction("schedule", &Timer::schedule)
			.endClass()
	.endNamespace();
}

void Timer::schedule(int interval, TimerCallback callable) {
	TimerEntry entry{callable, interval};
	entries.push_back(entry);
}

void Timer::tick() {
	for (TimerEntry& i : entries) {
		if (curTick % i.interval == 0) {
			// fire the callback
			i.callable(curTick);
		}
	}
	curTick++;
}
