/*
 * ITimerCallback.h
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#ifndef ITIMERCALLBACK_H_
#define ITIMERCALLBACK_H_

#include "Timer.h"

class ITimerCallback {
public:
	virtual ~ITimerCallback();
protected:
	virtual void onTimer(int tick) = 0;
	friend class Timer;
};

#endif /* ITIMERCALLBACK_H_ */
