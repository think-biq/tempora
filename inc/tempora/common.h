// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file common.h
	\brief Retrieve path to temp directories.

	^^
*/

#ifndef _H_TEMPORA_COMMON_H_
#define _H_TEMPORA_COMMON_H_

#ifdef _WIN32
#define TEMPORA_PATH_SIZE 32768
#else
#define TEMPORA_PATH_SIZE 255
#endif

enum tempora_temp_dir_type {
	TEMPORA_ERROR = 0,
	TEMPORA_ENV = 1,
	TEMPORA_PLATFORM = 2,
	TEMPORA_CWD = 3
};
typedef
	enum tempora_temp_dir_type
	tempora_temp_dir_type_t;

#endif