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
#include "ILuaClass.h"

class Timer;
typedef std::shared_ptr<Timer> TimerRef;

typedef std::function<void(int)> TimerCallback;

class Timer : public ILuaClass<Timer> {
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

namespace luabridge {
	template <> struct Stack<TimerCallback> {
		static void push(lua_State *l, TimerCallback f) {
			throw "pushing TimerCallback is not supported yet!";
		}
		
		static TimerCallback get(lua_State *l, int index) {
			LuaRef func = Stack<LuaRef>::get(l, index);
			return [=](int tick) {
				func(tick);
			};
		}
	};
}

LUA_MAKE_REF(Timer);

#endif /* TIMER_H_ */
