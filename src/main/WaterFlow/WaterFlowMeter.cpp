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

	WaterFlowMeter::WaterFlowMeter(IN uint8_t sensorPin, IN float sensorCalibrationFactor)
		: WaterFlowSensor(sensorPin) {
		_sensorCalibrationFactor = sensorCalibrationFactor;
	}

	WaterFlowMeter::~WaterFlowMeter() { /* Do Nothing */ }

	bool WaterFlowMeter::begin() {
		if (!_isInitialized && WaterFlowSensor::begin()) {
			_totalAmountFlowedLiters = _currentFlowRate = 0.0f;
			_isInitialized = true;
		}
		return _isInitialized;
	}

	void WaterFlowMeter::end() {
		if (_isInitialized) {
			WaterFlowSensor::end();
		}
	}

	void WaterFlowMeter::updateFlow() {
		unsigned long currentTime = millis();
		if (_isInitialized && (currentTime - _lastFlowUpdateTimestamp) > MIN_TIME_BETWEEN_UPDATES) {
			disablePulseCounting();
			// The flow formula: Pulses/Sec(Hz) = (sensorCalibrationFactor * Liters/Min) +- 3%
			_currentFlowRate = (_pulseCounter / ((currentTime - _lastFlowUpdateTimestamp) / 1000.0f))  / _sensorCalibrationFactor;
			_totalAmountFlowedLiters += _currentFlowRate * ((currentTime - _lastFlowUpdateTimestamp) / 60000.0f);
			_pulseCounter = 0;
			_lastFlowUpdateTimestamp = currentTime;
			if (_currentFlowRate == 0.0f) {
				_isFlowing = false;
			}
			else {
				_isFlowing = true;
			}
			enablePulseCounting();
		}
	}

	float WaterFlowMeter::getFlowRate() const {
		return _currentFlowRate;
	}

	float WaterFlowMeter::getTotalAmountFlowedLiters() const {
		return _totalAmountFlowedLiters;
	}

	void WaterFlowMeter::resetTotalAmountFlowed() {
		if (_isInitialized) {
			_totalAmountFlowedLiters = 0.0f;
		}
	}

};