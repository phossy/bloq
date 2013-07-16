/*
 * Timer.h
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#ifndef TIMER_H_
#define TIMER_H_

class ITimerCallback;
#include "ITimerCallback.h"
#include <list>
#include <memory>

class Timer;
typedef std::shared_ptr<Timer> TimerRef;

class Timer {
public:
	virtual ~Timer();
	Timer();

	void schedule(ITimerCallback& callable, int interval);
	void tick();
private:
	struct TimerEntry {
		ITimerCallback& callable;
		int interval;
	};
	std::list<TimerEntry> entries;

	int curTick;
};

#endif /* TIMER_H_ */
