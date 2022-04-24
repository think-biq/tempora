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

char*
_tempora_getcwd(char* path, unsigned int max_size) {
	return getcwd(path, max_size);
}

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

char*
_tempora_realpath(const char* partial, char* real, unsigned int max_size) {
    return realpath(partial, real);
}

char*
_tempora_dirname(const char* path) {
    return dirname(path);
}