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
#include "../../DistanceMeterAccurate.h"

namespace Easyuino {

	DistanceMeterAccurate::DistanceMeterAccurate(IN uint8_t triggerPin, IN uint8_t echoPin)
		: DistanceMeterNonBlock(triggerPin, echoPin) {
		_airTemperature = DEFAULT_AIR_TEMPERATURE_CELSIUS;
		_temperatureScale = CELSIUS;
	}

	DistanceMeterAccurate::DistanceMeterAccurate(IN uint8_t triggerEchoPin)
		: DistanceMeterAccurate(triggerEchoPin, triggerEchoPin) {
		/* Do Nothing */
	}

	DistanceMeterAccurate::~DistanceMeterAccurate() { /* Do Nothing */ }


	float DistanceMeterAccurate::getDistanceCentimeters() {
		return calculateDistance(CalculateSoundSpeed(_airTemperature, _temperatureScale));
	}

	void DistanceMeterAccurate::updateDistance(IN float airTemperature, IN TemperatureScale temperatureScale) {
		if (_isInitialized) {
			if (!_isEchoing || (_isEchoing && isUpdateDistanceNonBlockTimeout())) {
				_airTemperature = airTemperature;
				_temperatureScale = temperatureScale;
				executeUpdateDistanceBlock(CalculateSoundSpeed(_airTemperature, _temperatureScale));
			}
		}
	}

	void DistanceMeterAccurate::updateDistanceNonBlock(IN float airTemperature, IN TemperatureScale temperatureScale) {
		if (_isInitialized) {
			if (!_isEchoing || (_isEchoing && isUpdateDistanceNonBlockTimeout())) {
				_airTemperature = airTemperature;
				_temperatureScale = temperatureScale;
				executeUpdateDistanceNonBlock();
			}
		}
	}

	float DistanceMeterAccurate::CalculateSoundSpeed(IN float airTemperature, IN TemperatureScale temperatureScale) {
		float celsiusAirTemperature;
		switch (temperatureScale) {
		case TemperatureScale::FAHRENHEIT:
			celsiusAirTemperature = (airTemperature - 32) * 0.5556f;
			break;
		case TemperatureScale::KELVIN:
			celsiusAirTemperature = airTemperature - 273.15f;
			break;
		default:
			celsiusAirTemperature = airTemperature;
			break;
		}
		return 0.59f * celsiusAirTemperature + 33150.0f;
	}

};