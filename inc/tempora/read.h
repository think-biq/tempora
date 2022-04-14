// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.
/*! \file read.h
	\brief Retrieve path to temp directories.

	^^
*/

#ifndef _H_TEMPORA_READ_H_
#define _H_TEMPORA_READ_H_

enum tempora_temp_dir_type;

tempora_temp_dir_type_t
tempora_read(char* path, unsigned int size);

#endif