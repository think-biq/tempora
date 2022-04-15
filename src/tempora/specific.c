// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#if defined(WIN32)
#include <processenv.h>
#endif

#include <tempora/common.h>
#include <tempora/specific.h>

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
_tempora_getenv(const char* env_var) {
	#if defined(_WIN32_WCE) || defined(CURL_WINDOWS_APP)
	(void)env_var; // Signal variable not being used.
	return NULL;
	#elif defined(WIN32)
	// Courtesy to curl development community:
	// https://github.com/curl/curl/issues/4774
	/* This uses Windows API instead of C runtime getenv() to get the environment
	 variable since some changes aren't always visible to the latter. #4774 */
	char *buf = NULL;
	char *tmp;
	DWORD bufsize;
	DWORD rc = 1;

	for(;;) {
		tmp = realloc(buf, rc);
		if(!tmp) {
			free(buf);
			return NULL;
		}

		buf = tmp;
		bufsize = rc;

		/* It's possible for rc to be 0 if the variable was found but empty.
		   Since getenv doesn't make that distinction we ignore it as well. */
		rc = GetEnvironmentVariableA(env_var, buf, bufsize);
		if(!rc || rc == bufsize || rc > 32768) {
			free(buf);
			return NULL;
		}

		/* if rc < bufsize then rc is bytes written not including null */
		if(rc < bufsize)
			return buf;

		/* else rc is bytes needed, try again */
	}
	#else
	char *env = getenv(env_var);
	return (env && env[0]) 
		? strdup(env)
		: NULL
		;
	#endif
}

int
tempora_read_from_env(char* path, unsigned int size) {
	static const char *env_vars[] = {
		"TMPDIR",
		"TEMP",
		"TMP",
		// RiscOS
		"Wimp$ScrapDir"
	};
	static const uint8_t env_vars_count =
		sizeof env_vars / sizeof *env_vars;

	for (int i = 0; env_vars[i]; i++) {
		char *value = getenv(env_vars[i]);
		if (NULL != value) {
			if(0 == _tempora_is_directory(value)) {
				strncpy(path, value, size);
				#if defined(WIN32)
				free(value);
				#endif
				return 1;
			}
			#if defined(WIN32)
			free(value);
			#endif
		}
	}

	return 0;
}

int
tempora_read_from_platform_path(char* path, unsigned int size) {
	static const char *platform_paths[] = {
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
		sizeof platform_paths / sizeof *platform_paths;

	for (int i = 0; i < paths_count; i++) {
		if (0 == _tempora_is_directory(platform_paths[i])) {
			strncpy(path, platform_paths[i], size);
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