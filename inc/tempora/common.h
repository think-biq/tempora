// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file common.h
	\brief Retrieve path to temp directories.

	^^
*/

#ifndef _H_TEMPORA_COMMON_H_
#define _H_TEMPORA_COMMON_H_

#ifdef _WIN32
/**
 * Maximum available path size.
 */
#define TEMPORA_PATH_SIZE 32768
#else
/**
 * Maximum available path size.
 */
#define TEMPORA_PATH_SIZE 255
#endif

/**
 * @brief      Defines the type of temporary directory read by tempora.
 */
enum tempora_temp_dir_type {
	TEMPORA_ERROR		= 0,	/**< Error getting path. */
	TEMPORA_ENV			= 1,	/**< Path found in environment variable. */
	TEMPORA_PLATFORM	= 2,	/**< Path found in common platform paths. */
	TEMPORA_CWD			= 3		/**< Path found in current working directory. */
};

/**
 * @brief      Typedef for temp dir types.
 * 
 * @see tempora_temp_dir_type
 */
typedef
	enum tempora_temp_dir_type
	tempora_temp_dir_type_t;

/**
 * @brief      Finds the string representation of given directory type.
 *
 * @param[in]  dir_type  The directory type.
 *
 * @return     String representing the directory type.
 */
const char*
tempora_dir_type_name(enum tempora_temp_dir_type dir_type);

#endif