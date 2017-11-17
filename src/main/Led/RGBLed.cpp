/*
MIT License

Copyright (c) 2017 Andr� Pires

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
#include "../../RGBLed.h"

namespace Easyuino {

	RGBLed::RGBLed(IN uint8_t redPin, IN uint8_t greenPin, IN uint8_t bluePin)
		: RGBLed(redPin, greenPin, bluePin, LedType::COMMON_CATODE ) {	// Default: Common Catode
		/* Do Nothing */
	}

	RGBLed::RGBLed(IN uint8_t redPin, IN uint8_t greenPin, IN uint8_t bluePin, IN LedType ledType) {
		_redPin = redPin;
		_greenPin = greenPin;
		_bluePin = bluePin;
		_ledType = ledType;
	}

	RGBLed::~RGBLed() { /* Do Nothing */ }

	bool RGBLed::begin() {
		if (!_isInitialized) {
			pinMode(_redPin, OUTPUT);
			pinMode(_greenPin, OUTPUT);
			pinMode(_bluePin, OUTPUT);
			_isInitialized = true;
			return true;
		}
		return false;
	}

	void RGBLed::end() {
		if (_isInitialized) {
			turnOff();
			_isInitialized = false;
		}
	}

	void RGBLed::turnOff() {
		if (_isInitialized) {
			setColor(0, 0, 0);
		}
	}

	void RGBLed::setColor(IN uint8_t red, IN uint8_t green, IN uint8_t blue) {
		if (_isInitialized) {
			if (red >= 0 && red <= 255 &&
				green >= 0 && green <= 255 &&
				blue >= 0 && blue <= 255) {
				if (_ledType == LedType::COMMON_ANODE) {
					red = 255 - red;
					green = 255 - green;
					blue = 255 - blue;
				}
				analogWrite(_redPin, red);
				analogWrite(_greenPin, green);
				analogWrite(_bluePin, blue);
			}
		}
	}


	void RGBLed::setColor(IN char hexadecimalColorCode[8]) {
		uint8_t red, green, blue;
		char temp[5] = "0X\0\0";
		for (uint8_t i = 0; i < 8; i++) {
			char currentChar = hexadecimalColorCode[i];
			if ((i == 0 && currentChar != '#') ||
				(i == 7 && currentChar != '\0')||
				(i != 0 && i != 7 && !isHexadecimalDigit(currentChar))) {
				return;
			}
		}
		temp[2] = hexadecimalColorCode[1]; temp[3] = hexadecimalColorCode[2];
		red = (uint8_t)strtol(temp, NULL, 16);
		temp[2] = hexadecimalColorCode[3]; temp[3] = hexadecimalColorCode[4];
		green = (uint8_t)strtol(temp, NULL, 16);
		temp[2] = hexadecimalColorCode[5]; temp[3] = hexadecimalColorCode[6];
		blue = (uint8_t)strtol(temp, NULL, 16);
		setColor(red, green, blue);
	}

	void RGBLed::setColor(IN Color color) {
		if (_isInitialized) {
			switch (color)
			{
			case Color::RED:
				setColor(255, 0, 0);
				break;
			case Color::GREEN:
				setColor(0, 255, 0);
				break;
			case Color::BLUE:
				setColor(0, 0, 255);
				break;
			case Color::YELLOW:
				setColor(255, 255, 0);
				break;
			case Color::WHITE:
				setColor(255, 255, 255);
				break;
			case Color::ORANGE:
				setColor(255, 165, 0);
				break;
			case Color::PINK:
				setColor(255, 192, 203);
				break;
			case Color::SALMON:
				setColor(250, 128, 114);
				break;
			case Color::VIOLET:
				setColor(238, 130, 238);
				break;
			case Color::AQUA:
				setColor(0, 255, 255);
				break;
			case Color::BROWN:
				setColor(165, 42, 42);
				break;
			case Color::DARKGREY:
				setColor(165, 169, 169);
				break;
			case Color::OLIVE:
				setColor(128, 128, 0);
				break;
			case Color::SKYBLUE:
				setColor(135, 206, 235);
				break;
			case Color::FIREBRICK:
				setColor(178, 34, 34);
				break;
			default:
				break;
			}
		}
	}

}