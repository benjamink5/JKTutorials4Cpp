#pragma once

#include "TestDriverInterface.h"
#include <curl/curl.h>

namespace ExerciseCurlSamples
{
	class BaseTestDriver : public TestDriverInterface
	{
	public:
		BaseTestDriver();
		virtual ~BaseTestDriver();

		virtual void Execute();

	protected:
		virtual bool Initialize();
		virtual void Destroy();

		CURL * _pCurlHandle;
	};
}

