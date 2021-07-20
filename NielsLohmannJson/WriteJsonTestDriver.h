#pragma once

#include "TestDriver.h"

namespace ExerciseNielsLohmannJson
{
	class WriteJsonTestDriver : public TestDriver
	{
	public:
		WriteJsonTestDriver();
		~WriteJsonTestDriver();

		void Execute();
	};
}
