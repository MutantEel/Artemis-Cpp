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
			virtual void deserialize(Json::Value data);
			virtual const char* getTypeName();

		protected:
			Component();
	};

}

//these macros are for "automated" serialization
#define ARTEMIS_SERIALIZATION_SETUP(name)\
public: virtual const char* getTypeName()\
{\
return #name;\
}\
public: virtual Component* clone()\
{\
return new name();\
}\


#define ARTEMIS_SERIALIZE_START \
public: virtual Json::Value serialize() \
{\
Json::Value result;


#define ARTEMIS_SERIALIZE_END \
return result; \
}

#define ARTEMIS_SERIALIZE(var) \
result[#var] = var;



#define ARTEMIS_DESERIALIZE_START \
public: virtual void deserialize(Json::Value data) \
{\
if(data.isNull())\
{\
return;\
}


#define ARTEMIS_DESERIALIZE_END \
}

//possible types are Bool, CString, Double, Float, Int, Int64, String, UInt, UInt64 
#define ARTEMIS_DESERIALIZE(var, type, defaultValue) \
if(data.isMember(#var) && data[#var].is##type())\
{\
var = data[#var].as##type();\
}\
else\
{\
var = defaultValue;\
}

#endif
