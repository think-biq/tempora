// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file read.h
	\brief Retrieve path to temp directories.

	^^
*/

#ifndef _H_TEMPORA_SPECIFIC_H_
#define _H_TEMPORA_SPECIFIC_H_

uint8_t
tempora_read_from_env(char* path, unsigned int size);

uint8_t
tempora_read_from_platform_dirs(char* path, unsigned int size);

uint8_t
tempora_read_from_cwd(char* path, unsigned int size);

#endif