//
//  ComponentRegistry.cpp
//  Artemis
//
//  Created by Sean on 7/23/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#include <Artemis/ComponentRegistry.hpp>

namespace artemis
{

	bool ComponentRegistry::registerComponent(Component* component)
	{
		if(component && component->getTypeName())
		{
			components[component->getTypeName()] = component;
			return true;
		}

		return false;
	}


	Component* ComponentRegistry::createComponent(std::string name)
	{
		std::map<std::string, Component*>::iterator itr = components.find(name);

		if(itr != components.end())
		{
			return itr->second->clone();
		}

		return NULL;
	}


	void ComponentRegistry::reset()
	{
		for(std::map<std::string, Component*>::iterator itr = components.begin(); itr != components.end(); itr++)
		{
			delete itr->second;
		}

		components.clear();
	}

	std::map<std::string, Component*> ComponentRegistry::components;
}