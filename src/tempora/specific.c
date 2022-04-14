// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file specific.c
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

#include <tempora/specific.h>

/**
 * Check if the file at `path` exists and is a directory.
 *
 * Returns `0` if both checks pass, and `-1` if either fail.
 */
int
_tempora_is_directory(const char *path) {
	static struct stat s;
	if (-1 == stat(path, &s)) {
		return -1;
	}

	return 1 == S_ISDIR(s.st_mode)
		? 0
		: -1
		;
}

uint8_t
tempora_read_from_env(char* path, unsigned int size) {
	static const char *env_vars[] = {
		"TMPDIR",
		"TEMP",
		"TMP",
		// RiscOS (4.1)
		"Wimp$ScrapDir",
		NULL,
	};

	// check ENV vars (1, 2, 3)
	for (int i = 0; env_vars[i]; i++) {
		char *dir = getenv(env_vars[i]);
		if (dir && 0 == _tempora_is_directory(dir)) {
			strncpy(path, dir, size);
			return 1;
		}
	}

	return 0;
}

uint8_t
tempora_read_from_platform_dirs(char* path, unsigned int size) {
	#ifdef _WIN32
	// 4.2
	static const char *platform_dirs[] = {
		"C:\\TEMP",
		"C:\\TMP",
		"\\TEMP",
		"\\TMP",
		NULL,
	};
	#else
	// 4.3
	static const char *platform_dirs[] = {
		"/tmp",
		"/var/tmp",
		"/usr/tmp",
		NULL,
	};
	#endif

	// platform-specific checks (4)
	for (int i = 0; platform_dirs[i]; i++) {
		if (0 == _tempora_is_directory(platform_dirs[i])) {
			strncpy(path, platform_dirs[i], size);
			return 1;
		}
	}

	return 0;
}

uint8_t
tempora_read_from_cwd(char* path, unsigned int size) {
	#ifdef _WIN32
	#define _TEMPORA_PATH_SIZE 256
	#else
	#define _TEMPORA_PATH_SIZE 4096
	#endif
	static char cwd[_TEMPORA_PATH_SIZE] = {0};
	if (NULL != getcwd(cwd, sizeof(cwd))) {
		strncpy(path, cwd, size);
		return 1;
	}

	return 0;
}