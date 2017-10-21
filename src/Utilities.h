/*
Utilities.h
*/
#ifndef _EASYUINO_UTILITIES_h
#define _EASYUINO_UTILITIES_h

#include <string.h>
#include <stdlib.h>

namespace Easyuino {

	/*
	Provides some auxiliary functions for internal use in library but at same time expose it to public
	for the library users.
	*/
	class Utilities {

		public:
			/*
			Wrapper around the stdlib.h malloc to make it safe of overflows in the the majority of common
			string manipulation cases and at same time zero's all the allocated memory too.
			*/
			static void* EasyMalloc(unsigned int sizeInBytes);

	};

};

#endif
