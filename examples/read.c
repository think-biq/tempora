// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.

#include <stdio.h>

#include <tempora/all.h>

int main () {
	char path[TEMPORA_PATH_SIZE];
	tempora_temp_dir_type_t t = tempora_read(path, TEMPORA_PATH_SIZE);
	if (TEMPORA_ERROR == t) {
		printf("Could not read temp directory :/\n");
		return 1;
	}

	printf("Temp path: %s (type: %s)\n", path, tempora_dir_type_name(t));
	return 0;
}