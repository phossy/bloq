/*
 * Config.h
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define TEST_NO_CONFIG

#include <string>
#include <memory>

class Config;
typedef std::shared_ptr<Config> ConfigRef;

class Config {
public:
	Config();
	Config(const std::string& configFile);
	template<class T> T get(const std::string& key);
	template<class T> void set(const std::string& key, T value);
	virtual ~Config();
};

#endif /* CONFIG_H_ */
