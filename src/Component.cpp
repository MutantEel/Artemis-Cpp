#include <Artemis/Component.hpp>
#include <Artemis/World.hpp>

namespace artemis
{
	Component::Component()
	{
	}

	Component::~Component()
	{
	}

	Component* Component::clone()
	{
		return NULL;
	}

	Json::Value Component::serialize()
	{
		return Json::nullValue;
	}

	void Component::deserialize(Json::Value data)
	{
	}

	const char* Component::getTypeName()
	{
		return NULL;
	}
};
