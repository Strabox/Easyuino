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
			_cachedFlowRate = 0.0f;
			_currentMeasurementInitialTimestamp = millis();
			_previousMeasurementDuration = 0;
			_previousMeasurementPulses = 0;
			_currentMeasurementPulseCounter = 0;
			_isDirtyFlowRate = false;
			_isInitialized = true;
		}
		return _isInitialized;
	}

	void WaterFlowMeter::end() {
		if (_isInitialized) {
			WaterFlowSensor::end();
		}
	}

	float WaterFlowMeter::getFlowRateLitersMin()  {
		if (!isFlowing()) {
			return 0.0f;
		}
		else if (!_isDirtyFlowRate) {
			return _cachedFlowRate;
		}
		else {
			_isDirtyFlowRate = false;
			return _cachedFlowRate = (_previousMeasurementPulses / (_previousMeasurementDuration / 1000.0f)) / _sensorCalibrationFactor;
		}
	}

	void WaterFlowMeter::pulseHandler(IN unsigned long callTimestamp) {
		_lastPulseTimestamp = callTimestamp;
		_currentMeasurementPulseCounter++;
		if ((callTimestamp - _currentMeasurementInitialTimestamp) > MIN_TIME_BETWEEN_UPDATES) {
			_previousMeasurementDuration = callTimestamp - _currentMeasurementInitialTimestamp;
			_previousMeasurementPulses = _currentMeasurementPulseCounter;
			_currentMeasurementInitialTimestamp = callTimestamp;
			_currentMeasurementPulseCounter = 0;
			_isDirtyFlowRate = true;
		}
	}

};