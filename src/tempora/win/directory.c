// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <processenv.h>
#include <tchar.h>
#include <io.h>
#include <direct.h>
//#define getcwd _getcwd // MSFT "deprecation" warning in direct.h

#include <tempora/common.h>

// Use your own error codes here
#define SUCCESS                     0L
#define FAILURE_NULL_ARGUMENT       1L
#define FAILURE_API_CALL            2L
#define FAILURE_INSUFFICIENT_BUFFER 3L

char*
_tempora_getcwd(char* path, unsigned int max_size) {
	return _getcwd(path, max_size);
}

int
_tempora_is_directory(const char *path) {
	if(0 == _access( path, 0 )){

		struct stat status;
		stat(path, &status);

		return 0 != (status.st_mode & S_IFDIR)
			? 0
			: -1
			;
	}
	return 0;
}

char*
_tempora_realpath(const char* partial, char* real, unsigned int max_size) {
	//return _fullpath(real, partial, max_size);
	DWORD r = GetFullPathName(partial,
				 max_size,
				 real,
				 NULL);
	if (0 == r) {
		memset(real, 0, max_size);
	}

	return real;
}


// Thanks to https://stackoverflow.com/users/744056/andrewdski for his excellent
// answer on stackoverflow. https://stackoverflow.com/a/6074471
DWORD GetBasePathFromPathName(LPCTSTR szPathName,
							  LPTSTR  szBasePath,
							  DWORD   dwBasePathSize)
{
	TCHAR   szDrive[_MAX_DRIVE] = { 0 };
	TCHAR   szDir[_MAX_DIR]     = { 0 };
	TCHAR   szFname[_MAX_FNAME] = { 0 };
	TCHAR   szExt[_MAX_EXT]     = { 0 };
	size_t  PathLength;
	DWORD   dwReturnCode;

	// Parameter validation
	if( szPathName == NULL || szBasePath == NULL )
	{
		return FAILURE_NULL_ARGUMENT;
	}

	// Split the path into it's components
	dwReturnCode = _tsplitpath_s( szPathName, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, szFname, _MAX_FNAME, szExt, _MAX_EXT );
	if( dwReturnCode != 0 )
	{
		_ftprintf( stderr, TEXT("Error splitting path. _tsplitpath_s returned %d.\n"), dwReturnCode );
		return FAILURE_API_CALL;
	}

	// Check that the provided buffer is large enough to store the results and a terminal null character
	PathLength = _tcslen( szDrive ) + _tcslen( szDir );
	if( ( PathLength + sizeof( TCHAR ) ) > dwBasePathSize )
	{
		_ftprintf( stderr, TEXT("Insufficient buffer. Required %d. Provided: %d\n"), PathLength, dwBasePathSize );
		return FAILURE_INSUFFICIENT_BUFFER;
	}

	// Copy the szDrive and szDir into the provide buffer to form the basepath
	if( ( dwReturnCode = _tcscpy_s( szBasePath, dwBasePathSize, szDrive ) ) != 0 )
	{
		_ftprintf( stderr, TEXT("Error copying string. _tcscpy_s returned %d\n"), dwReturnCode );
		return FAILURE_API_CALL;
	}
	if( ( dwReturnCode = _tcscat_s( szBasePath, dwBasePathSize, szDir ) ) != 0 )
	{
		_ftprintf( stderr, TEXT("Error copying string. _tcscat_s returned %d\n"), dwReturnCode );
		return FAILURE_API_CALL;
	}
	return SUCCESS;
}

char*
_tempora_dirname(const char* path) {
	static char path_buffer[TEMPORA_PATH_SIZE] = {0};
	const size_t l = strlen(path);
	const size_t max_size = l < TEMPORA_PATH_SIZE ? l : TEMPORA_PATH_SIZE;
	if (SUCCESS != GetBasePathFromPathName(path_buffer, path, max_size)) {
		return "";
	}
	return path_buffer;
}