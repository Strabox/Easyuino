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
SevenSegments.h
*/
#ifndef _EASYUINO_SEVEN_SEGMENTS_h
#define _EASYUINO_SEVEN_SEGMENTS_h

#include <string.h>
#include "Utilities.h"
#include "Device.h"

namespace Easyuino {

	/** SevenSegments API is used to interact with seven segments displays.
	@see Devices Supported:	 TM1637 Driver
	@see Devices Tested:	 TM1637 Driver
	*/
	class SevenSegments : public Device {

	private:
		/** */
		uint8_t _clkPin;
		/** */
		uint8_t _dataPin;

	public:
		SevenSegments(IN uint8_t clkPin, IN uint8_t dataPin);

		bool begin();
		
		/**
		
		*/
		bool begin(IN uint8_t brightness);

		void end();

		/**
		
		*/
		void setBrightness(IN uint8_t brightness);

		/**
		
		*/
		void print(IN uint8_t num, IN uint8_t position);

		/**
		
		*/
		void print(IN unsigned int num);

		/**
		
		*/
		void print(IN int num);

		/**
		
		*/
		void print(IN const char* string);

	private:
		/**

		*/
		void sendByte(IN uint8_t byte);
		
		/** */
		void start();

		/** */
		void stop();

		/** */
		void microDelay();

	};

};

#endif