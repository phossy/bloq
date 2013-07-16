/*
 * Application.h
 *
 *  Created on: Jul 8, 2013
 *      Author: jason
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "RenderWindow.h"
#include "Config.h"
#include "Timer.h"

#include <memory>

#define TICK 100

class Application {
public:
	Application(int argc, char **argv);
	virtual ~Application();
	int run();

private:
	RenderWindowRef renderWin;
	ConfigRef config;
	TimerRef timer;
};

#endif /* APPLICATION_H_ */
