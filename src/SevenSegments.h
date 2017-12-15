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
		/** Arduino pin connected to CLK pin */
		uint8_t _clkPin;
		/** Arduino pin connected to DATA pin */
		uint8_t _dataPin;

	public:
		/** Constructor
		@param clkPin Arduino pin connected to CLK pin 
		@param dataPin Arduino pin connected to DATA pin
		*/
		SevenSegments(IN uint8_t clkPin, IN uint8_t dataPin);

		/** Destructor */
		~SevenSegments();

		bool begin();
		
		/** Initializes the API and sets the brightness of the display
		@param brightness Level of display brightness. Accepted values are [0,7]
		*/
		bool begin(IN uint8_t brightness);

		void end();

		/** sets the brightness of the display
		@param brightness Level of display brightness. Accepted values are [0,7]
		*/
		void setBrightness(IN uint8_t brightness);

		/** Print the digit (0-9) to the seven segment display of the position given. Position indexes
		start in the left [0,3].
		@param digit Digit to be displayed
		@param position Position to where display the digit
		*/
		void print(IN uint8_t digit, IN uint8_t position);

		/** Print the unsigned number given using all the display. If the number has more digits than display can represent
		the number is truncated and only the less significative digits are represented.
		@param number Number to be displayed
		*/
		void print(IN unsigned int number);

		/** Print the signed number given using all the display. If the number has more digits than display can represent
		the number is truncated and only the less significative digits are represented.
		@param number Number to be displayed
		*/
		void print(IN int number);

		/** Print the string in to the display. If the string has more chars than the display can represent the string is
		truncated and only the first chars are represented. Attention: Characters thar are not letters or numbers are skipped!
		@param string The string to be displayed
		*/
		void print(IN const char* string);

	private:
		/** Sends a byte of information to the display driver using its specific protocol
		@param byte Byte to send into the display driver
		*/
		void sendByte(IN uint8_t byte);
		
		/** Start must be called before sending a byte sendByte() to the display */
		void start();

		/** Stop must be called after sending a byte sendByte() to the display */
		void stop();

		/** Used to have micro delays between writes to the pins */
		void microDelay();

	};

};

#endif