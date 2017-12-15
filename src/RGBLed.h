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
RGBLed.h
*/
#ifndef _EASYUINO_RGB_LED_h
#define _EASYUINO_RGB_LED_h

#include "Utilities.h"
#include "Device.h"

namespace Easyuino {

	/** Types of RGB physical leds */
	enum LedType : uint8_t {
		COMMON_ANODE,
		COMMON_CATODE
	};

	/** Set of pre-defined colors that the RGBLed API knows how to reproduce */
	enum Color : uint8_t {
		RED, GREEN, BLUE, YELLOW, WHITE, ORANGE, PINK, SALMON, VIOLET, AQUA, BROWN,
		FIREBRICK, DARKGREY, OLIVE, SKYBLUE
	};

	/** RGBLed API allows to easily interact with a RGB led to set its color for example */
	class RGBLed : public Device {
	
	private:
		/** Type of the led defined by the enumerate LED_TYPE */
		LedType _ledType;

		/** Arduino pin connected do led's red pin */
		uint8_t _redPin;
		/** Arduino pin connected to led's green pin */
		uint8_t _greenPin;
		/** Arduino pin connected to led's blue pin */
		uint8_t _bluePin;

	public:
		/** Constructor for a COMMON CATODE RGBLed
		@param redPin	Arduino pin connected do led's red pin
		@param greenPin Arduino pin connected to led's green pin
		@param bluePin	Arduino pin connected to led's blue pin
		*/
		RGBLed(IN uint8_t redPin, IN uint8_t greenPin, IN uint8_t bluePin);

		/** Constructor
		@param redPin	Arduino pin connected do led's red pin
		@param greenPin Arduino pin connected to led's green pin
		@param bluePin	Arduino pin connected to led's blue pin
		@param ledType	Type of the RGB led
		*/
		RGBLed(IN uint8_t redPin, IN uint8_t greenPin, IN uint8_t bluePin, IN LedType ledType);

		/* Destructor */
		~RGBLed();

	#pragma region Public Device API Methods

		bool begin();

		void end();

	#pragma endregion

	#pragma region Public RGBLed API Methods 

		/** Turns off the led. It can be lit again using any setColor() methods. */
		void turnOff();

		/** Set the led's color based on the RGB code 
		@param red		Red value	(0-255)	
		@param green	Green value	(0-255)
		@param blue		Blue value	(0-255)
		*/
		void setColor(IN uint8_t red, IN uint8_t green, IN uint8_t blue);

		/** Set the led's color based on the hexadecimal color code (highly used in web development)
		@param hexadecimalColorCode	String that represents a valid hexadecimal color code (e.g: "#ffffff" to red color)
		*/
		void setColor(IN char hexadecimalColorCode[8]);

		/** Set the led's color based in a set o pre defined colors
		@param color Value that represents the color
		*/
		void setColor(IN Color color);

	#pragma endregion

	};

};

#endif
