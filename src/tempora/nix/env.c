// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libgen.h>
#include <unistd.h>

#include <tempora/common.h>
#include <tempora/specific.h>

char*
_tempora_getenv(const char* variable) {
	char *env = getenv(variable);
	return (NULL != env && '\0' != env[0])
		? strdup(env)
		: NULL
		;
}