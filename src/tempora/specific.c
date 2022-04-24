// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <tempora/common.h>
#include <tempora/specific.h>

int
_tempora_is_directory(const char *path);

char*
_tempora_getenv(const char* variable);

char*
_tempora_realpath(const char* partial, char* real, unsigned int max_size);

char*
_tempora_dirname(const char* path);

int
tempora_read_from_env(char* path, unsigned int size) {
	static const char *known_variables[] = {
		"TMPDIR",
		"TEMP",
		"TMP",
		"Wimp$ScrapDir" // RiscOS
	};
	static const uint8_t known_variables_count =
		sizeof known_variables / sizeof *known_variables;

	for (int i = 0; i < known_variables_count; i++) {
		char *value = _tempora_getenv(known_variables[i]);
		if (NULL != value && 0 < strlen(value)) {
			if(0 == _tempora_is_directory(value)) {
				char* selected_path = strdup(value);
				const unsigned int l = strlen(selected_path);
				// Make sure path is normalized.
				if (NULL == _tempora_realpath(value, selected_path, l)) {
					return 0;
				}

				strncpy(path, selected_path, size);
				free(selected_path);
				free(value);

				return 1;
			}
			free(value);
		}
	}

	return 0;
}

int
tempora_read_from_platform_path(char* path, unsigned int size) {
	static const char *known_paths[] = {
	#ifdef _WIN32
		"C:\\TEMP",
		"C:\\TMP",
		"\\TEMP",
		"\\TMP"
	#else
		"/tmp",
		"/var/tmp",
		"/usr/tmp"
	#endif
	};
	static const uint8_t paths_count =
		sizeof known_paths / sizeof *known_paths;

	for (int i = 0; i < paths_count; i++) {
		const char* selected_path = known_paths[i];
		if (0 == _tempora_is_directory(selected_path)) {
			strncpy(path, selected_path, size);

			return 1;
		}
	}

	return 0;
}

int
tempora_read_from_cwd(char* path, unsigned int size) {
	static char cwd[TEMPORA_PATH_SIZE] = {0};

	unsigned int path_size = TEMPORA_PATH_SIZE <= size
		? TEMPORA_PATH_SIZE - 1
		: size
		;
	if (NULL != getcwd(cwd, sizeof(cwd))) {
		strncpy(path, cwd, path_size);
		return 1;
	}

	return 0;
}

int
tempora_build_temp_dir_from_cwd(char* path, char** argv, size_t max_path_length) {
	static char out_path[TEMPORA_PATH_SIZE] = {0};

	// We got path from where program was started.
	// So we append the directory part of the exe name in argv,
	// to put the temp file side-by-side with the exe.
	if (NULL == path || NULL == argv || 0 == strlen(path)) return 0;
	
	// Check if path ends with separator.
	if (TEMPORA_PATH_SEPARATOR_CHAR != path[strlen(path)-1]) {
		strcat(path, TEMPORA_PATH_SEPARATOR_STR);
	}

	// Append directory part of exe name.
	strcat(path, _tempora_dirname(argv[0]));
	// Make sure path is normalized.
	if (NULL == _tempora_realpath(path, out_path, TEMPORA_PATH_SIZE)) {
		return 0;
	}

	// Copy back to path.
	strcpy(path, out_path);
	return 1;
}