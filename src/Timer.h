/*
 * Timer.h
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <list>
#include <memory>

class Timer;
typedef std::shared_ptr<Timer> TimerRef;

#include "LuaClass.h"

typedef std::function<void(int)> TimerCallback;

class Timer : public LuaClass<Timer> {
public:
	virtual ~Timer();
	Timer();

	void schedule(int interval, TimerCallback func);
	void tick();
	
	static void registerLua(lua_State *l);
private:
	struct TimerEntry {
		TimerCallback callable;
		int interval;
	};
	std::list<TimerEntry> entries;

	int curTick;
};

#endif /* TIMER_H_ */
