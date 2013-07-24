//
//  main.cpp
//  Artemis-test
//
//  Created by Sean on 7/23/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#include <Artemis/ComponentRegistry.hpp>
#include <Artemis/json.h>

using namespace artemis;


class TestComp : public Component
{
	public:
		int x;
		int y;

		ARTEMIS_SERIALIZATION_SETUP(TestComp)

		ARTEMIS_SERIALIZE_START
		ARTEMIS_SERIALIZE(x)
		ARTEMIS_SERIALIZE(y)
		ARTEMIS_SERIALIZE_END

		ARTEMIS_DESERIALIZE_START
		ARTEMIS_DESERIALIZE(x, Int, 0)
		ARTEMIS_DESERIALIZE(y, Int, 0)
		ARTEMIS_DESERIALIZE_END
};


int main(int argc, const char* argv[])
{
	Json::Value testData;
	testData["x"] = 100;
	testData["y"] = 200;

	TestComp* tc = new TestComp();
	tc->deserialize(testData);

	std::cout << "Input data is: \"" << testData.toStyledString() << "\"" << std::endl;
	std::cout << "Deserialized Object Data x:" << tc->x << " y: " << tc->y << std::endl;
	std::cout << "Serialized Object data is: \"" << tc->serialize().toStyledString() << "\"" << std::endl;

	delete tc;

	return 0;
}

