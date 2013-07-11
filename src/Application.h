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
	std::unique_ptr<RenderWindow> renderWin;
	std::unique_ptr<Config> config;
	std::unique_ptr<Timer> timer;
};

#endif /* APPLICATION_H_ */
