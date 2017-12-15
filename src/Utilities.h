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

#include <Wire.h>
#include <string.h>
#include <stdlib.h>

/** Define Easyuino API method parameter to be exclusively an input */
#define IN
/** Define Easyuino API method parameter to be exclusively an output */
#define OUT
/** Define Easyuino API method parameter that is used as input and output */
#define INOUT

namespace Easyuino {

	/** Provides some auxiliary functions for internal use in library but at same
	time expose it to public for the library users.
	*/
	class Utilities {

	public:
		/** Wrapper around the stdlib.h malloc to make it safe of overflows in the the majority
		of common string manipulation cases and at same time zero's all the allocated memory too.
		@param	sizeInBytes Amount of bytes to be allocated
		@return ptr Pointer to the first byte of the allocated memory
		*/
		static void* EasyMalloc(IN unsigned int sizeInBytes);

		/** Fills a given buffer with zeros aka \0.
		@param buffer		Pointer to the buffer
		@param bufferSize	Buffer's size
		*/
		static void ZeroBuffer(IN void *buffer, IN size_t bufferSize);

		/** Put a \0 in the last character of the string.
		@param string	Pointer to the string
		*/
		static void OverrideLastStringChar(IN char* string);

		/** Put a \0 in the last two characters of the string.
		@param string	Pointer to the string
		*/
		static void OverrideLastTwoChar(IN char* string);

		/** Obtain the addresses of all devices connected to Arduino using I2C.
		It scans all the addresses to see if someone is on the other side.
		Based on http://playground.arduino.cc/Main/I2cScanner.
		
		*/
		static void ObtainI2CDeviceAddress(INOUT int* listOfAddresses, IN uint8_t sizeOfList);

	};

};

#endif
