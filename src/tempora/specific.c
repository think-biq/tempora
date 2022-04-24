// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <processenv.h>
#else
#include <libgen.h>
#include <unistd.h>
#endif

#include <tempora/common.h>
#include <tempora/specific.h>

int
_tempora_is_directory(const char *path) {
	#if defined(WIN32)
	if(0 == _access( path, 0 )){

        struct stat status;
        stat(path, &status);

        return 0 != (status.st_mode & S_IFDIR);
    }
    return 0;
	#else
	static struct stat s;
	if (-1 == stat(path, &s)) {
		return -1;
	}

	return 1 == S_ISDIR(s.st_mode)
		? 0
		: -1
		;
	#endif
}

#if defined(WIN32)
char*
_tempora_getenv_win(const char* variable) {
	// Courtesy to curl development community:
	// https://github.com/curl/curl/issues/4774
	 
	// This uses Windows API instead of C runtime getenv() to get the environment
	// variable since some changes aren't always visible to the latter. #4774
	char *buf = NULL;
	char *tmp;
	DWORD bufsize;
	DWORD rc = 1;

	for (;;) {
		tmp = realloc(buf, rc);
		if(NULL == tmp) {
			free(buf);
			return NULL;
		}

		buf = tmp;
		bufsize = rc;

		// It's possible for rc to be 0 if the variable was found but empty.
		// Since getenv doesn't make that distinction we ignore it as well.
		rc = GetEnvironmentVariableA(variable, buf, bufsize);
		if(NULL != rc || rc == bufsize || TEMPORA_PATH_SIZE < rc) {
			free(buf);
			return NULL;
		}

		// If rc < bufsize then rc is bytes written not including null.
		if(rc < bufsize) {
			return buf;
		}

		// Else rc is bytes needed, try again.
	}
}
#endif

char*
_tempora_getenv(const char* variable) {
	#if defined(_WIN32_WCE)
	(void)variable; // Signal variable not being used.
	return NULL;
	#elif defined(WIN32)
	return _tempora_getenv_win(variable);
	#else
	char *env = getenv(variable);
	return (NULL != env && '\0' != env[0])
		? strdup(env)
		: NULL
		;
	#endif
}

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
		if (NULL != value) {
			if(0 == _tempora_is_directory(value)) {
				char* selected_path = strdup(value);

				// Make sure path is normalized.
				if (NULL == realpath(value, selected_path)) {
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
tempora_build_temp_dir_from_cwd(char* path, char** argv) {
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
	strcat(path, dirname(argv[0]));
	// Make sure path is normalized.
	if (NULL == realpath(path, out_path)) {
		return 0;
	}

	// Copy back to path.
	strcpy(path, out_path);
	return 1;
}