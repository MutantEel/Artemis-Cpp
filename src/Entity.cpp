#include <Artemis/Entity.hpp>
#include <sstream>
#include <Artemis/Component.hpp>
#include <Artemis/World.hpp>
#include <Artemis/ComponentRegistry.hpp>

using namespace std;

namespace artemis
{

	Entity::Entity(World* world, int id)
	{
		this->world = world;
		this->entityManager = world->getEntityManager();
		this->id = id;
	}

	Entity::~Entity()
	{
		world = NULL;
		entityManager = NULL;
	}


	void Entity::addSystemBit(bitset<BITSIZE> bit)
	{
		systemBits |= bit;
	}

	void Entity::addTypeBit(bitset<BITSIZE> bit)
	{
		typeBits |= bit;
	}

	Component* Entity::getComponent(ComponentType& type)
	{
		return entityManager->getComponent(*this, type);
	}

	ImmutableBag<Component*>& Entity::getComponents()
	{
		return entityManager->getComponents(*this);
	}

	int Entity::getId()
	{
		return id;
	}

	bitset<BITSIZE> Entity::getSystemBits()
	{
		return systemBits;
	}

	bitset<BITSIZE> Entity::getTypeBits()
	{
		return typeBits;
	}

	long int Entity::getUniqueId()
	{
		return uniqueId;
	}

	bool Entity::isActive()
	{
		return entityManager->isActive(this->getId());
	}

	void Entity::refresh()
	{
		world->refreshEntity(*this);
	}

	void Entity::addComponent(Component* c)
	{
		entityManager->addComponent(*this, c);
	}

	void Entity::removeComponent(ComponentType& type)
	{
		entityManager->removeComponent(*this, type);
	}

	void Entity::removeSystemBit(bitset<BITSIZE> bit)
	{
		systemBits &= ~bit;
	}

	void Entity::removeTypeBit(bitset<BITSIZE> bit)
	{
		typeBits &= ~bit;
	}

	void Entity::reset()
	{
		typeBits = 0;
		systemBits = 0;
	}

	void Entity::setGroup(string group)
	{

		world->getGroupManager()->set(group, *this);
	}

	void Entity::setSystemBits(bitset<BITSIZE> systemBits)
	{
		this->systemBits = systemBits;
	}

	void Entity::setTag(string tag)
	{
		world->getTagManager()->subscribe(tag, *this);
	}

	Json::Value Entity::serialize()
	{
		ImmutableBag<Component*>& comps = getComponents();
		Json::Value result;
		
		//save tag
		std::string tag = world->getTagManager()->tagForEntity(*this);
		
		if(!tag.empty())
		{
			result["artemis_tag"] = tag;
		}
		
		//save group
		std::string group = world->getGroupManager()->getGroupOf(*this);
		
		if(!group.empty())
		{
			result["artemis_group"] = group;
		}

		//serialize all component
		for(int i = 0; i < comps.getCount(); i++)
		{
			Component* c = comps.get(i);

			if(c && c->getTypeName())
			{
				result[c->getTypeName()] = c->serialize();
			}
		}

		return result;
	}

	void Entity::deserialize(Json::Value data)
	{
		if(data.isNull() || !data.isObject())
		{
			return;
		}
		
		//get tag
		if(data.isMember("artemis_tag") && data["artemis_tag"].isString())
		{
			setTag(data["artemis_tag"].asString());
		}
		
		//get group
		if(data.isMember("artemis_group") && data["artemis_group"].isString())
		{
			world->getGroupManager()->set(data["artemis_group"].asString(), *this);
		}

		//create components and deserialize all members
		Json::Value::Members members = data.getMemberNames();

		for(Json::Value::Members::iterator itr = members.begin(); itr != members.end(); itr++)
		{
			Component* c = ComponentRegistry::createComponent(itr->c_str());

			if(c)
			{
				c->deserialize(data[itr->c_str()]);
				addComponent(c);
			}
		}
		
		refresh();
	}

	void Entity::setTypeBits(bitset<BITSIZE> typeBits)
	{
		this->typeBits = typeBits;
	}

	void Entity::setUniqueId(long int uniqueId)
	{
		this->uniqueId = uniqueId;
	}

	std::string Entity::toString()
	{
		std::ostringstream oss;
		oss << "Entity[" << id << "]\n";
		return  oss.str();
	}

	void Entity::remove()
	{
		world->deleteEntity(*this);
	}
};
