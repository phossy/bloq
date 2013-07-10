/*
 * Config.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#include "Config.h"

Config::Config() {

}

Config::Config(const std::string& configFile) {

}

template<> int Config::get<int>(const std::string& key) {
#ifdef TEST_NO_CONFIG
	if (key.compare("width") == 0) {
		return 1024;
	} else if (key.compare("height") == 0) {
		return 768;
	}
#endif
	return 0;
}

template<> bool Config::get<bool>(const std::string& key) {
#ifdef TEST_NO_CONFIG
	if (key.compare("fullscreen") == 0) {
		return false;
	}
#endif
	return false;
}

Config::~Config() {
	// TODO Auto-generated destructor stub
}

