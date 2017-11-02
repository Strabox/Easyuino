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
#include "../../WaterFlowMeter.h"

namespace Easyuino {

	WaterFlowMeter* WaterFlowMeter::Singleton;

	WaterFlowMeter::WaterFlowMeter(IN uint8_t sensorPin) {
		_sensorPin = sensorPin;
		if (Singleton != NULL) {
			delete Singleton;
		}
		Singleton = this;
	}

	WaterFlowMeter::~WaterFlowMeter() { 
		Singleton = NULL;
	}

	bool WaterFlowMeter::begin() {
		if (!_isInitialized) {
			pinMode(_sensorPin, INPUT);
			digitalWrite(_sensorPin, HIGH);
			attachInterrupt(digitalPinToInterrupt(_sensorPin), InterruptCaller, FALLING);
			_pulseCounter = 0;
			_lastCheckTimestamp = 0;
			_flowRate = 0.0f;
			_isInitialized = true;
		}
		return _isInitialized;
	}

	void WaterFlowMeter::end() {
		if (_isInitialized) {
			detachInterrupt(digitalPinToInterrupt(_sensorPin));
			_isInitialized = false;
		}
	}

	void WaterFlowMeter::updateFlowRate() {
		detachInterrupt(digitalPinToInterrupt(_sensorPin));
		_flowRate = (1000.0 / (millis() - _lastCheckTimestamp)) * _pulseCounter / _sensorCalibration;
		_lastCheckTimestamp = millis();
		_pulseCounter = 0;
		attachInterrupt(digitalPinToInterrupt(_sensorPin), InterruptCaller, FALLING);
	}

	bool WaterFlowMeter::isFlowing() {
		if (_flowRate < 0.001f) {
			return false;
		}
		else {
			return true;
		}
	}

	float WaterFlowMeter::getFlowRate() {
		return 0.0f;
	}

	void WaterFlowMeter::countPulses() {
		_pulseCounter++;
	}

	/* Static */
	void WaterFlowMeter::InterruptCaller() {
		if (Singleton != NULL) {
			Singleton->countPulses();
		}
	}

};