// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.

#include <stdio.h>

#include <tempora/all.h>

int evaluate_path(char* path, tempora_path_type_t t, char** argv, size_t max_path_length) {
	switch(t) {
		case TEMPORA_ERROR:
			printf("Could not read temp directory :/\n");
		break;
		case TEMPORA_ENV:
			printf("Read from environment: %s\n", path);
		break;
		case TEMPORA_PLATFORM:
			printf("Read from platform specifc path: %s\n", path);
		break;
		case TEMPORA_CWD:
			if (tempora_build_temp_dir_from_cwd(path, argv, max_path_length)) {
				printf("Read from working directory: %s\n", path);
			}
			else {
				printf("Could not build side-by-side temp dir :/\n");
			}
		break;
		default:
			printf("Could not identify path type :/\n");
			return 0;
	}

	return 1;
}

int main (int argc, char** argv) {
	char path[TEMPORA_PATH_SIZE];
	tempora_path_type_t t;

	t = TEMPORA_ENV;
	if (tempora_read_from_env(path, TEMPORA_PATH_SIZE)) {
		if (0 == evaluate_path(path, t, argv, TEMPORA_PATH_SIZE)) return 1;
	}
	
	t = TEMPORA_PLATFORM;
	if (tempora_read_from_platform_path(path, TEMPORA_PATH_SIZE)) {
		if (0 == evaluate_path(path, t, argv, TEMPORA_PATH_SIZE)) return 1;
	}
	
	t = TEMPORA_CWD;
	if (tempora_read_from_cwd(path, TEMPORA_PATH_SIZE)) {
		if (0 == evaluate_path(path, t, argv, TEMPORA_PATH_SIZE)) return 1;
	}
	
	t = tempora_read(path, TEMPORA_PATH_SIZE);
	if (TEMPORA_ERROR != t) {
		if (0 == evaluate_path(path, t, argv, TEMPORA_PATH_SIZE)) return 1;
	}

	return 0;
}