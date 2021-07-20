#pragma once

#include "TestDriver.h"

namespace ExerciseNielsLohmannJson
{
	class ReadJsonTestDriver : public TestDriver
	{
	public:
		ReadJsonTestDriver();
		~ReadJsonTestDriver();

		void Execute();

	private:
		void runTestCase01();
	};
}