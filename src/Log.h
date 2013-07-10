/*
 * Log.h
 *
 *  Created on: Jul 9, 2013
 *      Author: jason
 */

#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <SDL2/SDL_log.h>

#define LOG_MAPPER(name, level) \
	template <class... Args> static inline void name(const std::string& fmt, Args... args) { \
		SDL_LogMessage(0, level, fmt.c_str(), args...); \
	}


class Log {
public:
	LOG_MAPPER(verbose, SDL_LOG_PRIORITY_VERBOSE);
	LOG_MAPPER(debug, SDL_LOG_PRIORITY_DEBUG);
	LOG_MAPPER(info, SDL_LOG_PRIORITY_INFO);
	LOG_MAPPER(warn, SDL_LOG_PRIORITY_WARN);
	LOG_MAPPER(error, SDL_LOG_PRIORITY_ERROR);
	LOG_MAPPER(critical, SDL_LOG_PRIORITY_CRITICAL);
};

#endif /* LOG_H_ */
