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
#include "../../Relay.h"

namespace Easyuino {

	Relay::Relay(uint8_t arduinoPin) : Device() {
		_arduinoPin = arduinoPin;
		_isOpen = false;
	}

	Relay::~Relay() { /* Do Nothing */ }

	void Relay::begin() {
		begin(HIGH);	// Default is HIGH
	}

	void Relay::begin(uint8_t closedStatePinLevel) {
		if (!_isInitialized && (closedStatePinLevel == LOW || closedStatePinLevel == HIGH)) {
			pinMode(_arduinoPin, OUTPUT);
			digitalWrite(_arduinoPin, closedStatePinLevel);
			_isInitialized = true;
		}
	}

	void Relay::end() {
		if (_isInitialized) {
			close();
			_isInitialized = false;
		}
	}

	void Relay::open() {
		if (_isInitialized && !_isOpen) {
			if (digitalRead(_arduinoPin) == HIGH) {
				digitalWrite(_arduinoPin, LOW);
			}
			else {
				digitalWrite(_arduinoPin, HIGH);
			}
			_isOpen = true;
		}
	}

	void Relay::close() {
		if (_isInitialized && _isOpen) {
			if (digitalRead(_arduinoPin) == HIGH) {
				digitalWrite(_arduinoPin, LOW);
			}
			else {
				digitalWrite(_arduinoPin, HIGH);
			}
			_isOpen = false;
		}
	}

	bool Relay::isOpen() const {
		return _isOpen;
	}

};