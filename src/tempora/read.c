// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file tempora.c
	\brief Retrieve path to temp directories.

	^^
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>

#include <tempora/common.h>
#include <tempora/read.h>
#include <tempora/specific.h>


tempora_temp_dir_type_t
tempora_read(char* path, unsigned int size) {
	if (tempora_read_from_env(path, size)) {
		return TEMPORA_ENV;
	}
	else if (tempora_read_from_platform_path(path, size)) {
		return TEMPORA_PLATFORM;
	}
	else if (tempora_read_from_cwd(path, size)) {
		return TEMPORA_CWD;
	}

	return TEMPORA_ERROR;
}