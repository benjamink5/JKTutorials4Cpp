#pragma once

#include "BaseTestDriver.h"

namespace ExerciseCurlSamples
{
	class SimpleCurlTestDriver : public BaseTestDriver
	{
	public:
		SimpleCurlTestDriver();
		~SimpleCurlTestDriver();

		virtual void Execute();
	private:
	};
}

