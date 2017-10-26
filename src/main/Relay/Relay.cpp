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
	}

	Relay::~Relay() { /* Do Nothing */ }

	bool Relay::begin() {
		return begin(false, HIGH);	// Default is a device connected to a Normally Open terminal
	}

	bool Relay::begin(bool isNormallyClosed, uint8_t normallyClosedPinLevel) {
		if (!_isInitialized && (normallyClosedPinLevel == HIGH || normallyClosedPinLevel == LOW)) {
			pinMode(_arduinoPin, OUTPUT);
			digitalWrite(_arduinoPin, normallyClosedPinLevel);
			if (isNormallyClosed) {
				_isOn = true;
			}
			else {
				_isOn = false;
			}
			_isInitialized = true;
			return true;
		}
		return false;
	}

	void Relay::end() {
		if (_isInitialized) {
			turnOff();
			_isInitialized = false;
		}
	}

	void Relay::turnOn() {
		if (_isInitialized && !_isOn) {
			if (digitalRead(_arduinoPin) == HIGH) {
				digitalWrite(_arduinoPin, LOW);
			}
			else {
				digitalWrite(_arduinoPin, HIGH);
			}
			_isOn = true;
		}
	}

	void Relay::turnOff() {
		if (_isInitialized && _isOn) {
			if (digitalRead(_arduinoPin) == HIGH) {
				digitalWrite(_arduinoPin, LOW);
			}
			else {
				digitalWrite(_arduinoPin, HIGH);
			}
			_isOn = false;
		}
	}

	bool Relay::isOn() const {
		return _isOn;
	}

};