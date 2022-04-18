// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file read.h
	\brief Retrieve path to temp directories.

	^^
*/

#ifndef _H_TEMPORA_READ_H_
#define _H_TEMPORA_READ_H_

#include "common.h"

/**
 * @brief      Try reading the first available temporary file storage directory.
 * 
 * @see enum tempora_path_type
 *
 * @param      path  Pointer to the path buffer to be populated.
 * @param[in]  size  Size of the path buffer.
 *
 * @return     Type of temporary directory.
 */
tempora_path_type_t
tempora_read(char* path, unsigned int size);

#endif