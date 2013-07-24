#ifndef COMPONENT_H
#define COMPONENT_H

#include <Artemis/json.h>

namespace artemis
{
	
	/**
	 * A tag class. All components in the system must extend this class.
	 */
	class Component
	{
		public:
			virtual ~Component() = 0;
			virtual Component* clone();
			virtual Json::Value serialize();
		
		protected:
			Component();
	};

}

//these macros are for "automated" serialization

#define ARTEMIS_SERIALIZE_START \
public: virtual Json::Value serialize() \
{\
Json::Value result;


#define ARTEMIS_SERIALIZE_END \
return result; \
}

#define ARTEMIS_SERIALIZE(var) \
result["##var"] = var;

#endif
