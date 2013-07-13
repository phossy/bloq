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

typedef std::function<std::shared_ptr<Entity>() > EntityPrototype;

class EntityFactory {
public:
	EntityFactory();
	virtual ~EntityFactory();

	void registerPrototype(const std::string& name, EntityPrototype creator);
	std::shared_ptr<Entity> create(const std::string& name);
private:
	std::map<const std::string, EntityPrototype> creators;
};

#endif /* ENTITYFACTORY_H_ */
