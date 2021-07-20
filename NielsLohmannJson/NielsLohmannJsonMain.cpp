// NielsLohmannJson.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;
using namespace ExerciseNielsLohmannJson;

void ExecuteReadJsonTestDriver();
void ExecuteWriteJsonTestDriver();

int main()
{
	ExecuteReadJsonTestDriver();

	ExecuteWriteJsonTestDriver();
}

// Test to read from a json data
void ExecuteReadJsonTestDriver()
{
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "\tTest to read from a json data" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;

	// Start up
	TestDriver * pTestDriver = NULL;

	// Execute
	pTestDriver = new ReadJsonTestDriver();
	pTestDriver->Execute();

	// Clean up
	if (pTestDriver != NULL)
	{
		delete pTestDriver;
		pTestDriver = NULL;
	}

	cout << endl;
}

// Test to write into a json data
void ExecuteWriteJsonTestDriver()
{
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "\tTest to write into a json data" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;

	// Start up
	TestDriver * pTestDriver = NULL;

	// Execute
	pTestDriver = new WriteJsonTestDriver();
	pTestDriver->Execute();

	// Clean up
	if (pTestDriver != NULL)
	{
		delete pTestDriver;
		pTestDriver = NULL;
	}

	cout << endl;
}
