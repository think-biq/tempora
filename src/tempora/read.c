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
	// 1. The directory named by the TMPDIR environment variable.
	// 2. The directory named by the TEMP environment variable.
	// 3. The directory named by the TMP environment variable.
	if (tempora_read_from_env(path, size)) {
		return TEMPORA_ENV;
	}
	// 4. A platform-specific location:
	//   4.1 On RiscOS, the directory named by the Wimp$ScrapDir
	//       environment variable.
	//   4.2 On Windows, the directories C:\TEMP, C:\TMP, \TEMP,
	//       and \TMP, in that order.
	//   4.3 On all other platforms, the directories /tmp,
	//       /var/tmp, and /usr/tmp, in that order.
	else if (tempora_read_from_platform_dirs(path, size)) {
		return TEMPORA_PLATFORM;
	}
	// 5. As a last resort, the current working directory.
	else if (tempora_read_from_cwd(path, size)) {
		return TEMPORA_CWD;
	}

	return TEMPORA_ERROR;
}