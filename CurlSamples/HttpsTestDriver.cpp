#include "HttpsTestDriver.h"

#include <iostream>
#include <cassert>

using namespace std;
namespace ExerciseCurlSamples
{
	void HttpsTestDriver::Execute()
	{
		CURLcode res;

		assert(_pCurlHandle != NULL);

		if (!_pCurlHandle)
		{
			throw "The Curl handle is not defined!!!";
		}

		char* szCurlVersion = curl_version();
		cout << szCurlVersion << endl;

		curl_easy_setopt(_pCurlHandle, CURLOPT_URL, "https://google.com");
		//curl_easy_setopt(_pCurlHandle, CURLOPT_FOLLOWLOCATION, 1L);

		//curl_easy_setopt(_pCurlHandle, CURLOPT_CAPATH, ".");
#ifdef SKIP_PEER_VERIFICATION
		/*
		 * If you want to connect to a site who isn't using a certificate that is
		 * signed by one of the certs in the CA bundle you have, you can skip the
		 * verification of the server's certificate. This makes the connection
		 * A LOT LESS SECURE.
		 *
		 * If you have a CA cert for the server stored someplace else than in the
		 * default bundle, then the CURLOPT_CAPATH option might come handy for
		 * you.
		 */
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
		/*
		 * If the site you're connecting to uses a different host name that what
		 * they have mentioned in their server certificate's commonName (or
		 * subjectAltName) fields, libcurl will refuse to connect. You can skip
		 * this check, but this will make the connection less secure.
		 */
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
		// Perform the request, res will get the return code
		res = curl_easy_perform(_pCurlHandle);
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
	}
}
