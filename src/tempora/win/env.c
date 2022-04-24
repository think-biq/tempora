// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.

#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <processenv.h>

#include <tempora/common.h>
#include <tempora/specific.h>

char*
_tempora_getenv(const char* variable) {
	#if defined(_WIN32_WCE)
	(void)variable; // Signal variable not being used.
	return NULL;
	#elif defined(WIN32)
	// Courtesy to curl development community:
	// https://github.com/curl/curl/issues/4774
	 
	// This uses Windows API instead of C runtime getenv() to get the environment
	// variable since some changes aren't always visible to the latter. #4774
	char* buffer = NULL;
	DWORD bufsize = 0;
	DWORD rc = 8;

	for (;;) {
		buffer = malloc(rc);
		if(NULL == buffer) {
			return NULL;
		}

		bufsize = rc;
		// Make sure it is null-terminated https://stackoverflow.com/a/62039256.
		memset(buffer, 0, bufsize);


		// It's possible for rc to be 0 if the variable was found but empty.
		// Since getenv doesn't make that distinction we ignore it as well.
		rc = GetEnvironmentVariableA(variable, buffer, bufsize);
		if(0 == rc) {
			return strdup("");
		}

		// If rc < bufsize then rc is bytes written not including null.
		if(rc < bufsize) {
			return buffer;
		}

		// Else rc is bytes needed, try again.
		free(buffer);
		buffer = NULL;
	}
	#else
	#warning "Trying to build windows specific enviroment variable function!"
	#endif
}