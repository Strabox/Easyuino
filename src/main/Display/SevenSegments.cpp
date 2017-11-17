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
#include "../../SevenSegments.h"

#define INITIALIZE 7

namespace Easyuino {

	//TODO: Implementation soon

	SevenSegments::SevenSegments(uint8_t clkPin, uint8_t dataPin) : Device() {
		_clkPin = clkPin;
		_dataPin = dataPin;
	}

	bool SevenSegments::begin() {
		if (!_isInitialized) {
			print(INITIALIZE);
			_isInitialized = true;
		}
		return _isInitialized;
	}

	void SevenSegments::end() {
		if (_isInitialized) {
			_isInitialized = false;
		}
	}

	void SevenSegments::print(uint8_t byte) {
		start();
		for (uint8_t i = 0; i < 8; i++)
		{
			digitalWrite(_clkPin, LOW);
			delayMicroseconds(5);
			digitalWrite(_dataPin, (byte & (1 << i)) >> i);
			delayMicroseconds(5);
			digitalWrite(_clkPin, HIGH);
			delayMicroseconds(5);
		}

		// wait for ACK 
		digitalWrite(_clkPin, LOW);
		delayMicroseconds(5);

		pinMode(_dataPin, INPUT);

		digitalWrite(_clkPin, HIGH);
		delayMicroseconds(5);

		bool ack = digitalRead(_dataPin) == 0;

		pinMode(_dataPin, OUTPUT);
		stop();
	}

	void SevenSegments::start() {
		digitalWrite(_clkPin, HIGH);	//send start signal to TM1637 
		digitalWrite(_dataPin, HIGH);
		delayMicroseconds(5);

		digitalWrite(_dataPin, LOW);
		digitalWrite(_clkPin, LOW);
		delayMicroseconds(5);
	}

	void SevenSegments::stop() {
		digitalWrite(_clkPin, LOW);
		digitalWrite(_dataPin, LOW);
		delayMicroseconds(5);

		digitalWrite(_clkPin, HIGH);
		digitalWrite(_dataPin, HIGH);
		delayMicroseconds(5);
	}


}
