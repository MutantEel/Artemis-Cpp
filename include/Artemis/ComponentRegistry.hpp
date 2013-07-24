//
//  ComponentRegistry.hpp
//  Artemis
//
//  Created by Sean on 7/23/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//


#ifndef Artemis_ComponentRegistry_hpp
#define Artemis_ComponentRegistry_hpp

#include <map>
#include <string>
#include <Artemis/Component.hpp>

namespace artemis
{

	/**
	 * The component registry is a place to register components by name. This allows components to be serializable
	 * easily
	 */
	class ComponentRegistry
	{

		public:

			template<typename c>
			static bool registerComponent()
			{
				return registerComponent(new c());
			}

			static bool registerComponent(Component* component);

			static Component* createComponent(const char* name);

			static void reset();

		protected:

			static std::map<const char*, Component*> components;
	};
}

#endif
