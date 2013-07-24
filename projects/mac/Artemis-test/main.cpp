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
	


	ARTEMIS_SERIALIZE_START
		ARTEMIS_SERIALIZE(x)
		ARTEMIS_SERIALIZE(y)
	ARTEMIS_SERIALIZE_END
};


int main(int argc, const char * argv[])
{
	TestComp* tc = new TestComp();
	
	return 0;
}

