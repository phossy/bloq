/*
 * EntityFactory.h
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#ifndef ENTITYFACTORY_H_
#define ENTITYFACTORY_H_

#include "Entity.h"

#include <functional>
#include <string>
#include <map>

class EntityFactory {
public:
	EntityFactory();
	virtual ~EntityFactory();

	void registerCreator(const std::string& name, std::function<std::shared_ptr<Entity>()> creator);
	std::shared_ptr<Entity> create(const std::string& name);
private:
	std::map<const std::string, std::function<std::shared_ptr<Entity>()> > creators;
};

#endif /* ENTITYFACTORY_H_ */
