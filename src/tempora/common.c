// 2022-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
// See license.md for details.

#include <tempora/common.h>

const char*
tempora_dir_type_name(enum tempora_temp_dir_type dir_type) {
	switch(dir_type) {
		case TEMPORA_ERROR:
			return "TEMPORA_ERROR";
		break;
		case TEMPORA_ENV:
			return "TEMPORA_ENV";
		break;
		case TEMPORA_PLATFORM:
			return "TEMPORA_PLATFORM";
		break;
		case TEMPORA_CWD:
			return "TEMPORA_CWD";
		break;
	}

	return 0;
}