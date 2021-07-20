// SDLTutorials.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "SDLTutorial01.h"
#include "SDLTutorial02.h"

using namespace std;
using namespace JK_SDLTutorials;

int main()
{
    
	BaseTestDriver * tester = new SDLTutorial02();

	tester->Initialize();

	tester->Execute();

	tester->Destroy();

	delete tester;

	return 0;
}

