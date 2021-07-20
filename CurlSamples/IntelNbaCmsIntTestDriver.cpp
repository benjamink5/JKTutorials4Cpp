#include "IntelNbaCmsIntTestDriver.h"

#include <iostream>
#include <cassert>

using namespace std;

namespace ExerciseCurlSamples
{
	void IntelNbaCmsIntTestDriver::Execute()
	{
		CURLcode res;

		assert(_pCurlHandle != NULL);

		if (!_pCurlHandle)
		{
			throw "The Curl handle is not defined!!!";
		}

		char* szCurlVersion = curl_version();
		cout << szCurlVersion << endl;

		curl_easy_setopt(_pCurlHandle, CURLOPT_URL, "https://api.cms-np.sports.intel.com/int/v1/exp/nba/appconfig/config/16d9fffa-dc74-43d3-a6f7-1188ced5ef2a");
		curl_easy_setopt(_pCurlHandle, CURLOPT_FOLLOWLOCATION, 1L);

		curl_easy_setopt(_pCurlHandle, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(_pCurlHandle, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		curl_easy_setopt(_pCurlHandle, CURLOPT_USERPWD, "admin:634cZ-E4DVSm_xwE");
		curl_easy_setopt(_pCurlHandle, CURLOPT_PINNEDPUBLICKEY, "sha256//t7V3K1JnssEVW269UAfID+SqNnkpx/d7ULLd5oxHqko=");

#ifdef WIN32
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
		curl_easy_setopt(_pCurlHandle, CURLOPT_SSL_VERIFYPEER, 0L);
#else
		curl_easy_setopt(_pCurlHandle, CURLOPT_SSL_VERIFYPEER, 1L);
#endif
		/*
		 * If the site you're connecting to uses a different host name that what
		 * they have mentioned in their server certificate's commonName (or
		 * subjectAltName) fields, libcurl will refuse to connect. You can skip
		 * this check, but this will make the connection less secure.
		 */
		curl_easy_setopt(_pCurlHandle, CURLOPT_SSL_VERIFYHOST, 1L);

#ifdef _DEBUG
		curl_easy_setopt(_pCurlHandle, CURLOPT_CERTINFO, 1L);
#endif

		// The following code snippet shows how to add the request headers.
		/*
		struct curl_slist *chunk = NULL;

		// Remove a header curl would otherwise add by itself
		chunk = curl_slist_append(chunk, "Accept:");

		// Add a custom header
		chunk = curl_slist_append(chunk, "Another: yes");

		// Modify a header curl otherwise adds differently
		chunk = curl_slist_append(chunk, "Host: example.com");

		// Add a header with "blank" contents to the right of the colon. Note that
		//   we're then using a semicolon in the string we pass to curl!
		chunk = curl_slist_append(chunk, "X-silly-header;");

		// set our custom set of headers
		curl_easy_setopt(_pCurlHandle, CURLOPT_HTTPHEADER, chunk);
		*/

		// Perform the request, res will get the return code
		res = curl_easy_perform(_pCurlHandle);
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

#ifdef _DEBUG
		struct curl_certinfo *certinfo;

		res = curl_easy_getinfo(_pCurlHandle, CURLINFO_CERTINFO, &certinfo);

		if (!res && certinfo) {
			int i;

			printf("%d certs!\n", certinfo->num_of_certs);

			for (i = 0; i < certinfo->num_of_certs; i++) {
				struct curl_slist *slist;

				for (slist = certinfo->certinfo[i]; slist; slist = slist->next)
					printf("%s\n", slist->data);

			}
		}
#endif
	}
}