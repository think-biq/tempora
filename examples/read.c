
#include <stdio.h>

#include <tempora/all.h>


int main () {
	char path[TEMPORA_PATH_SIZE];
	tempora_temp_dir_type_t t = tempora_read(path, TEMPORA_PATH_SIZE);
	if (TEMPORA_ERROR == t) {
		printf("Could not read temp directory :/\n");
		return 1;
	}

	printf("Temp path: %s\n", path);

	return 0;
}