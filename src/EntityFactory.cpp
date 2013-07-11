/*
 * EntityFactory.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: jason
 */

#include "EntityFactory.h"

EntityFactory::EntityFactory() {
	// TODO Auto-generated constructor stub

}

EntityFactory::~EntityFactory() {
	// TODO Auto-generated destructor stub
}

void EntityFactory::registerCreator(const std::string& name, std::function<std::shared_ptr<Entity>() > creator) {
	if (creators.find(name) != creators.end()) {
		creators.insert({name, creator});
	}
}

std::shared_ptr<Entity> EntityFactory::create(const std::string& name) {
	if (creators.find(name) != creators.end()) {
		return creators.at(name)();
	}
	return nullptr;
}