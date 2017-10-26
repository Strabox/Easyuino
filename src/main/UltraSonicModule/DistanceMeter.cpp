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
#include "../../DistanceMeter.h"

namespace Easyuino {

	DistanceMeter::DistanceMeter(uint8_t triggerPin, uint8_t echoPin) : Device() {
		_triggerPin = triggerPin;
		_echoPin = echoPin;
		_distance = -1.0f;
		_isEchoing = false;
	}

	DistanceMeter::DistanceMeter(uint8_t triggerEchoPin) 
		: DistanceMeter(triggerEchoPin, triggerEchoPin) {
		/* Do Nothing */
	}

	DistanceMeter::~DistanceMeter() { /* Do Nothing */ }

	bool DistanceMeter::begin() {
		if (!_isInitialized) {
			if (_triggerPin != _echoPin) {
				pinMode(_triggerPin, OUTPUT);
				pinMode(_echoPin, INPUT);
				digitalWrite(_echoPin, LOW);
			}
			else {
				pinMode(_triggerPin, OUTPUT);
				digitalWrite(_triggerPin, LOW);
			}
			_isInitialized = true;
			return true;
		}
		return false;
	}

	void DistanceMeter::end() {
		if (_isInitialized) {
			_distance = -1;
			_isEchoing = false;
			_isInitialized = false;
		}
	}

	float DistanceMeter::getDistanceCentimeters() {
		return _distance;
	}

	float DistanceMeter::getDistanceInches() {
		return getDistanceCentimeters() * 0.3937007874f;		// Conversion centimeters to inches
	}

	void DistanceMeter::updateDistance() {
		if (_isInitialized) {
			if (!_isEchoing) {
				executeUpdateDistanceBlock(DEFAULT_SOUND_SPEED_CM_PER_SEC);
			}
		}
	}

	float DistanceMeter::executeUpdateDistanceBlock(float soundSpeedCmSec) {
		unsigned long echoTravelTime = 0;
		_isEchoing = true;
		if (_echoPin == _triggerPin) {		// Change the pin to output if it is 3 pin module to send echo
			pinMode(_triggerPin, OUTPUT);
		}
		digitalWrite(_triggerPin, LOW);
		delayMicroseconds(DELAY_AFTER_TRIGGER_LOW_MICROS);
		digitalWrite(_triggerPin, HIGH);
		delayMicroseconds(ECHO_PULSE_DURATION_MICROS);
		digitalWrite(_triggerPin, LOW);
		delayMicroseconds(DELAY_AFTER_TRIGGER_LOW_MICROS);
		if (_echoPin == _triggerPin) {		// Change the pin to input if it is 3 pin module to receive echo
			pinMode(_triggerPin, INPUT);
		}
		echoTravelTime = pulseIn(_echoPin, HIGH, ECHO_TIMEOUT_MICROS);
		if (echoTravelTime != 0) {
			_distance = echoTravelTime / 2000000.0f * soundSpeedCmSec;
		}
		_isEchoing = false;
	}

};