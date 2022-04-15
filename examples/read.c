// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.

#include <stdio.h>

#include <tempora/all.h>

//#define USE_ENV
//#define USE_PLATFORM
//#define USE_CWD

int main (int argc, char** argv) {
	char path[TEMPORA_PATH_SIZE];

	#if defined(USE_ENV)
	tempora_temp_dir_type_t t = TEMPORA_ENV;
	tempora_read_from_env(path, TEMPORA_PATH_SIZE);
	#elif defined(USE_PLATFORM)
	tempora_temp_dir_type_t t = TEMPORA_PLATFORM;
	tempora_read_from_platform_path(path, TEMPORA_PATH_SIZE);
	#elif defined(USE_CWD)
	tempora_temp_dir_type_t t = TEMPORA_CWD;
	tempora_read_from_cwd(path, TEMPORA_PATH_SIZE);
	#else
	tempora_temp_dir_type_t t = tempora_read(path, TEMPORA_PATH_SIZE);
	#endif
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
			if (tempora_build_temp_dir_from_cwd(path, argv)) {
				printf("Read from working directory: %s\n", path);
			}
			else {
				printf("Could not build side-by-side temp dir :/\n");
			}
		break;		
	}

	printf("Temp path: %s (type: %s)\n", path, tempora_dir_type_name(t));

	return 0;
}