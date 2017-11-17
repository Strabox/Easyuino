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
#include "../../WaterFlowMeter.h"

namespace Easyuino {

	WaterFlowMeter::WaterFlowMeter(IN uint8_t sensorPin) 
		: WaterFlowSensor(sensorPin) {
		/* Do Nothing */
	}

	WaterFlowMeter::~WaterFlowMeter() { /* Do Nothing */ }

	bool WaterFlowMeter::begin() {
		if (!_isInitialized && WaterFlowSensor::begin()) {
			_lastCheckTimestamp = 0;
			_flowRate = 0.0f;
			_isInitialized = true;
		}
		return _isInitialized;
	}

	void WaterFlowMeter::end() {
		if (_isInitialized) {
			WaterFlowSensor::end();
			_isInitialized = false;
		}
	}

	void WaterFlowMeter::updateFlowRate() {
		disablePulseCouning();
		_flowRate = ((millis() - _lastCheckTimestamp) / 1000.0f) * _pulseCounter / _sensorCalibrationFactor;
		_pulseCounter = 0;
		_lastCheckTimestamp = millis();
		enablePulseCounting();
	}

	bool WaterFlowMeter::isFlowing() {
		if (_flowRate < 1.0f) {
			return false;
		}
		else {
			return true;
		}
	}

	float WaterFlowMeter::getFlowRate() {
		_flowRate;
	}

};