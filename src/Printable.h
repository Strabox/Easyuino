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
Printable.h
*/

#ifndef _EASYUINO_PRINTABLE_h
#define _EASYUINO_PRINTABLE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif

namespace Easyuino {

	/*
	Provides some devices implementations with an interface to write themeselves to a stream.
	Useful for debug the current state of the device.
	*/
	class Printable {

	#pragma region Public Virtual Common API Methods

	public:
		/* Used to return a string representation of the Device state.
		IMPORTANT: It is mandatory to free the returned pointer in order to have no memory leaks. */
		virtual char* toString() const = 0;

	#pragma endregion

		/* Write the Device state string representation to a given stream (e.g: Used to Debug) */
		friend Stream& operator<<(Stream & stream, const Printable& printable);

	};

};

#endif
