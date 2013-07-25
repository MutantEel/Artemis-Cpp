//
//  main.cpp
//  Artemis-test
//
//  Created by Sean on 7/23/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#include <Artemis/ComponentRegistry.hpp>
#include <Artemis/json.h>
#include <Artemis/World.hpp>
#include <Artemis/SystemManager.hpp>
#include <Artemis/EntityManager.hpp>

using namespace artemis;


class Position : public Component
{
	public:
		int x;
		int y;

		ARTEMIS_SERIALIZATION_SETUP(Position)

		ARTEMIS_SERIALIZE_START
		ARTEMIS_SERIALIZE(x)
		ARTEMIS_SERIALIZE(y)
		ARTEMIS_SERIALIZE_END

		ARTEMIS_DESERIALIZE_START
		ARTEMIS_DESERIALIZE(x, Int, 0)
		ARTEMIS_DESERIALIZE(y, Int, 0)
		ARTEMIS_DESERIALIZE_END
};

class Velocity : public Component
{
public:
	float x;
	float y;
	
	ARTEMIS_SERIALIZATION_SETUP(Velocity)
	
	ARTEMIS_SERIALIZE_START
	ARTEMIS_SERIALIZE(x)
	ARTEMIS_SERIALIZE(y)
	ARTEMIS_SERIALIZE_END
	
	ARTEMIS_DESERIALIZE_START
	ARTEMIS_DESERIALIZE(x, Double, 0)
	ARTEMIS_DESERIALIZE(y, Double, 0)
	ARTEMIS_DESERIALIZE_END
};


int main(int argc, const char* argv[])
{
	Json::Value testData;
	
	{
		Json::Value entData;
		
		//position component
		Json::Value positionData;
		positionData["x"] = 100;
		positionData["y"] = 200;
		entData["Position"] = positionData;
	
		Json::Value velData;
		velData["x"] = 300.0;
		velData["y"] = 500.0;
		entData["Velocity"] = velData;
		
		testData[0] = entData;
	}
	
	
	ComponentRegistry::registerComponent<Position>();
	ComponentRegistry::registerComponent<Velocity>();
	

	artemis::World world;
	artemis::SystemManager* sm = world.getSystemManager();
	artemis::EntityManager* em = world.getEntityManager();
	
	sm->initializeAll();
	
	em->deserialize(testData);
	

	std::cout << "Input data is: \"" << testData.toStyledString() << "\"" << std::endl;
	std::cout << "Serialized Object data is: \"" << em->serialize().toStyledString() << "\"" << std::endl;

	return 0;
}

