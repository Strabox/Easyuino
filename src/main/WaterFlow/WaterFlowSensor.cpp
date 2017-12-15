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
#include "../../WaterFlowSensor.h"

namespace Easyuino {

	WaterFlowSensor* WaterFlowSensor::Singleton;

	WaterFlowSensor::WaterFlowSensor(IN uint8_t sensorPin) : Device() {
		_sensorPin = sensorPin;
		_lastPulseTimestamp = 0;
		if (Singleton != NULL) {
			delete Singleton;
		}
		Singleton = this;
	}

	WaterFlowSensor::~WaterFlowSensor() {
		Singleton = NULL;
	}

	bool WaterFlowSensor::begin() {
		if (!_isInitialized) {
			pinMode(_sensorPin, INPUT);
			_isInitialized = true;
			attachInterrupt(digitalPinToInterrupt(_sensorPin), WaterFlowSensor::InterruptCaller, FALLING);
		}
		return _isInitialized;
	}

	void WaterFlowSensor::end() {
		if (_isInitialized) {
			detachInterrupt(digitalPinToInterrupt(_sensorPin));
			_isInitialized = false;
		}
	}


	bool WaterFlowSensor::isFlowing() const {
		if (_isInitialized) {
			if ((millis() - _lastPulseTimestamp) > PULSE_TIMEOUT) {
				return false;
			}
			else {
				return true;
			}
		}
		return false;	//API not initialized
	}


	void WaterFlowSensor::pulseHandler(IN unsigned long callTimestamp) {
		_lastPulseTimestamp = callTimestamp;
	}

	/* Static */
	void WaterFlowSensor::InterruptCaller() {
		unsigned long callTime = millis();
		if (Singleton != NULL) {
			Singleton->pulseHandler(callTime);
		}
	}

};