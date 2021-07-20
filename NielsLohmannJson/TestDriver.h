#pragma once

#include <string>
namespace ExerciseNielsLohmannJson
{
	class TestDriver
	{
	public:
		TestDriver();
		virtual ~TestDriver();

		virtual void Execute() = 0;
	};
}

