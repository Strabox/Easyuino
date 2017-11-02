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
#include "../../WaterDetector.h"

namespace Easyuino {

	WaterDetector::WaterDetector(IN uint8_t digitalPin, IN uint8_t analogPin) 
		: Device() {
		_digitalPin = digitalPin;
		_analogPin = analogPin;
	}

	WaterDetector::~WaterDetector() { /* Do Nothing */ }

	bool WaterDetector::begin() {
		return begin(LOW);
	}

	bool WaterDetector::begin(IN uint8_t digitalPinTriggerLevel) {
		if (!_isInitialized && (digitalPinTriggerLevel == HIGH || digitalPinTriggerLevel == LOW)) {
			pinMode(_digitalPin, INPUT);
			_digitalPinTriggerLevel = digitalPinTriggerLevel;
			_isInitialized = true;
		}
		return _isInitialized;
	}

	void WaterDetector::end() {
		if (_isInitialized) {
			_isInitialized = false;
		}
	}

	WaterStatus WaterDetector::getWaterStatus() {
		if (_isInitialized) {
			unsigned int read = analogRead(_analogPin);
			if (read >= DRY_MAX_LEVEL) {
				return WaterStatus::DRY;
			}
			else if (read >= FEW_WATER_DROPS_MAX_LEVEL) {
				return WaterStatus::FEW_DROPS;
			}
			else if(read >= WET_MAX_LEVEL) {
				return WaterStatus::WET;
			}
			else if (read >= FLOOD_MAX_LEVEL) {
				return WaterStatus::FLOOD;
			}
			return WaterStatus::INVALID;
		}
		return WaterStatus::NOT_INITIALIZED;
	}

	unsigned int WaterDetector::getWaterStatusRange() {
		if (_isInitialized) {
			return analogRead(_analogPin);
		}
		return -1;
	}

	bool WaterDetector::isWaterDetected() {
		if (_isInitialized) {
			if (digitalRead(_digitalPin) == _digitalPinTriggerLevel) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}

}