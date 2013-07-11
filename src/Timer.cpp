/*
 * Timer.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#include "Timer.h"

Timer::Timer() : curTick(0) {
}

Timer::~Timer() {

}

void Timer::schedule(ITimerCallback& callable, int interval) {
	TimerEntry entry{callable, interval};
	entries.push_back(entry);
}

void Timer::tick() {
	for (TimerEntry& i : entries) {
		if (curTick % i.interval == 0) {
			// fire the callback
			i.callable.onTimer(curTick);
		}
	}
	curTick++;
}
