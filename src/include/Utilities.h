/*
MIT License

Copyright (c) 2017 André Pires

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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
