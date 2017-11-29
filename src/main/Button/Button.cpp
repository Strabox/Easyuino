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
#include "../../Button.h"

namespace Easyuino {

	Button::Button(IN uint8_t touchPin) : Device() {
		_touchPin = touchPin;
		_lastState = _currentState = LOW;
		_lastReadTimestamp = millis();
	}

	Button::~Button() { /* Do Nothing */ }

	bool Button::begin() {
		if (!_isInitialized) {
			pinMode(_touchPin, INPUT);
			_isInitialized = true;
		}
		return _isInitialized;
	}

	void Button::end() {
		if (_isInitialized) {
			_isInitialized = false;
		}
	}

	bool Button::isPressed() {
		uint8_t readingState = digitalRead(_touchPin);
		bool res;

		if (readingState != _lastState) {
			_lastReadTimestamp = millis();
		}

		if ((millis() - _lastReadTimestamp) > DEFAULT_DEBOUNCE_DELAY) {

			if (readingState != _currentState) {
				_currentState = readingState;
			}

		}
		_lastState = readingState;
		return _currentState == HIGH;
	}

};