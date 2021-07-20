#include "BaseTestDriver.h"

namespace ExerciseCurlSamples
{
	BaseTestDriver::BaseTestDriver()
	{
		Initialize();
	}

	BaseTestDriver::~BaseTestDriver()
	{
		Destroy();
	}

	bool BaseTestDriver::Initialize()
	{
		curl_global_init(CURL_GLOBAL_DEFAULT);

		_pCurlHandle = curl_easy_init();
		return (_pCurlHandle != NULL);
	}

	void BaseTestDriver::Destroy()
	{
		if (_pCurlHandle)
		{
			curl_easy_cleanup(_pCurlHandle);
		}

		curl_global_cleanup();
	}

	void BaseTestDriver::Execute()
	{

	}
}