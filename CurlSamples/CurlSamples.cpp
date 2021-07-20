// CurlSamples.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SimpleCurlTestDriver.h"
#include "HttpsTestDriver.h"
#include "IntelNbaCmsIntTestDriver.h"

using namespace ExerciseCurlSamples;

int main()
{
	TestDriverInterface* pTestDriver = NULL;

	pTestDriver = new IntelNbaCmsIntTestDriver();

	pTestDriver->Execute();

	if (pTestDriver)
	{
		delete pTestDriver;
		pTestDriver = NULL;
	}

	return 0;
}

