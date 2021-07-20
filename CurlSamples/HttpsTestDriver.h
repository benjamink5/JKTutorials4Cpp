#pragma once

#include "BaseTestDriver.h"

namespace ExerciseCurlSamples
{
	class HttpsTestDriver : public BaseTestDriver
	{
	public:
		HttpsTestDriver() {}
		~HttpsTestDriver() {}

		void Execute();
	};
}

