#include "SimpleCurlTestDriver.h"
#include <curl/curl.h>

#include <cassert>

using namespace std;

namespace ExerciseCurlSamples
{
	SimpleCurlTestDriver::SimpleCurlTestDriver()
	{
	}
	
	SimpleCurlTestDriver::~SimpleCurlTestDriver()
	{
	}

	void SimpleCurlTestDriver::Execute()
	{
		CURLcode res;

		assert(_pCurlHandle != NULL);

		if (!_pCurlHandle)
		{
			throw "The Curl handle is not defined!!!";
		}

		curl_easy_setopt(_pCurlHandle, CURLOPT_URL, "http://google.com");
		/* example.com is redirected, so we tell libcurl to follow redirection */
		curl_easy_setopt(_pCurlHandle, CURLOPT_FOLLOWLOCATION, 1L);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(_pCurlHandle);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",

				curl_easy_strerror(res));
	}
}