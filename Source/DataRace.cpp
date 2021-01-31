/*
  ==============================================================================

    DataRace.cpp
    Created: 14 Jan 2021 8:49:20pm
    Author:  bobby

  ==============================================================================
*/

#include "DataRace.h"

bool Data::operator==(const Data& other)
{
	return a == other.a && b == other.b;
}

bool Data::operator!=(const Data& other)
{
	return !(*this == other);
}

//====================================================

void A::run()
{
	while (true)
	{
		if (threadShouldExit())
			break;

		x = a;

		//compare
		if (x != a && x != b)
		{
			auto _local = x;
			std::cout << "A: "
				<< "x = { .a=" << String::toHexString(_local.a)
				<< ", .b=" << String::toHexString(_local.b) << " }" << std::endl;
		}
		wait( 10 );
	}
}

void B::run()
{
	while (true)
	{
		if (threadShouldExit())
			break;

		x = b;

		//compare
		if (x != a && x != b)
		{
			auto _local = x;
			std::cout << "B: "
				<< "x = { .a=" << String::toHexString(_local.a)
				<< ", .b=" << String::toHexString(_local.b) << " }" << std::endl;
		}
		wait(10);
	}
}
