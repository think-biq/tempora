// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file specific.h
	\brief Retrieve path to temp directories.

	^^
*/

#ifndef _H_TEMPORA_SPECIFIC_H_
#define _H_TEMPORA_SPECIFIC_H_

/**
 * @brief      Read the first available temporary file storage directory from 
 * most common environment variables.
 *
 * @param      path  Pointer to the path buffer to be populated.
 * @param[in]  size  Size of the path buffer.
 *
 * @return     Returns 0 < on Success, 0 on failure.
 */
int
tempora_read_from_env(char* path, unsigned int size);

/**
 * @brief      Read the first available temporary file storage directory from 
 * most common platform specific paths.
 *
 * @param      path  Pointer to the path buffer to be populated.
 * @param[in]  size  Size of the path buffer.
 *
 * @return     Returns 0 < on Success, 0 on failure.
 */
int
tempora_read_from_platform_path(char* path, unsigned int size);

/**
 * @brief      Read the path of the current working directory.
 *
 * @param      path  Pointer to the path buffer to be populated.
 * @param[in]  size  Size of the path buffer.
 *
 * @return     Returns 0 < on Success, 0 on failure.
 */
int
tempora_read_from_cwd(char* path, unsigned int size);

/**
 * @brief      Manipulates path in place to be side-by-side with program path.
 * 
 * Given the path result created by tempora_read_from_cwd, this function takes
 * the program name from argv and appends it.
 * 
 * @see tempora_read_from_cwd
 *
 * @param      path  Pointer to the path buffer to be populated.
 * @param      argv  Argument list passed to the program.
 * @param      max_path_length  Maximum space available at *path*.
 *
 * @return     Returns 0 < on Success, 0 on failure.
 */
int
tempora_build_temp_dir_from_cwd(char* path, char** argv, size_t max_path_length);

#endif