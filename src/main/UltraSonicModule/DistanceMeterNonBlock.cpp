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
#include "../../DistanceMeterNonBlock.h"

namespace Easyuino {

	DistanceMeterNonBlock* DistanceMeterNonBlock::INSTANCES[MAXIMUM_NUMBER_OF_DM_NON_BLOCK];

	DistanceMeterNonBlock::DistanceMeterNonBlock(IN uint8_t triggerPin, IN uint8_t echoPin)
		: DistanceMeter(triggerPin, echoPin) {
		_lastTimeTrigger = _lastTimeEcho = 0;
		_echoSent = false;
		_blockingMeasure = true;
		_isDirtyDistance = false;
		DistanceMeterNonBlock::assignInstance(this);
	}

	DistanceMeterNonBlock::DistanceMeterNonBlock(IN uint8_t triggerEchoPin)
		: DistanceMeterNonBlock(triggerEchoPin, triggerEchoPin) {
		/* Do Nothing */
	}

	DistanceMeterNonBlock::~DistanceMeterNonBlock() {
		detachInterrupt(digitalPinToInterrupt(_echoPin));
		DistanceMeterNonBlock::deleteInstance(this);
	}

	bool DistanceMeterNonBlock::begin() {
		if (!_isInitialized) {
			pinMode(_triggerPin, OUTPUT);
			pinMode(_echoPin, INPUT);
			digitalWrite(_echoPin, LOW);
			DistanceMeterNonBlock::attachInterruptToInstance(this);
			_isInitialized = true;
			return true;
		}
		return false;
	}

	void DistanceMeterNonBlock::end() {
		if (_isInitialized) {
			_distance = _lastTimeTrigger = _lastTimeEcho = 0;
			_isEchoing = _echoSent = false;
			_blockingMeasure = true;
			_isDirtyDistance = false;
			detachInterrupt(digitalPinToInterrupt(_echoPin));
			_isInitialized = false;
		}
	}

	float DistanceMeterNonBlock::getDistanceCentimeters() {
		return calculateDistance(DEFAULT_SOUND_SPEED_CM_PER_SEC);
	}

	void DistanceMeterNonBlock::updateDistance() {
		if (_isInitialized) {
			if (!_isEchoing || (_isEchoing && isUpdateDistanceNonBlockTimeout())) {
				_blockingMeasure = true;
				executeUpdateDistanceBlock(DEFAULT_SOUND_SPEED_CM_PER_SEC);
			}
		}
	}

	void DistanceMeterNonBlock::updateDistanceNonBlock() {
		if (_isInitialized) {
			if (!_isEchoing || (_isEchoing && isUpdateDistanceNonBlockTimeout())) {
				executeUpdateDistanceNonBlock();
			}
		}
	}

	void DistanceMeterNonBlock::executeUpdateDistanceNonBlock() {
		_blockingMeasure = false;
		_isEchoing = true;
		if (_echoPin == _triggerPin) {								// Used to 3 pin US
			detachInterrupt(digitalPinToInterrupt(_triggerPin));
			pinMode(_triggerPin, OUTPUT);
		}
		digitalWrite(_triggerPin, LOW);
		delayMicroseconds(DELAY_AFTER_TRIGGER_LOW_MICROS);
		digitalWrite(_triggerPin, HIGH);
		delayMicroseconds(ECHO_PULSE_DURATION_MICROS);
		digitalWrite(_triggerPin, LOW);
		delayMicroseconds(DELAY_AFTER_TRIGGER_LOW_MICROS);
		if (_echoPin == _triggerPin) {								// Used to 3 pin US
			DistanceMeterNonBlock::attachInterruptToInstance(this);
			pinMode(_triggerPin, INPUT);
		}
	}

	bool DistanceMeterNonBlock::isUpdateDistanceNonBlockTimeout() {
		if ((micros() - _lastTimeTrigger) > ECHO_TIMEOUT_MICROS) {	// Timeout for the non-block echo detected
			_echoSent = _isEchoing = false;
			return true;
		}
		return false;
	}

	float DistanceMeterNonBlock::calculateDistance(IN float soundSpeedCmPerSec) {
		if (!_isDirtyDistance) {
			return _distance;
		}
		else {
			_distance = ((_lastTimeEcho - _lastTimeTrigger) * soundSpeedCmPerSec) / 2000000.0f;
			_isDirtyDistance = false;
			return _distance;
		}
	}

	#pragma region Interrupt Management/Handling Methods
	
	void DistanceMeterNonBlock::interruptHandler(IN unsigned long interruptCallTimeMicros) {
		if (!_blockingMeasure) {
			if (digitalRead(_echoPin) == HIGH && _isEchoing && !_echoSent) {
				_lastTimeTrigger = interruptCallTimeMicros;
				_echoSent = true;
			}
			else if (digitalRead(_echoPin) == LOW && _isEchoing && _echoSent) {
				_lastTimeEcho = interruptCallTimeMicros;
				_isEchoing = _echoSent = false;
				_isDirtyDistance = true;
			}
		}
	}

	/* Static */
	void DistanceMeterNonBlock::assignInstance(IN DistanceMeterNonBlock* dm) {
		if (DistanceMeterNonBlock::INSTANCES[0] == NULL) {
			DistanceMeterNonBlock::INSTANCES[0] = dm;
		}
		else if (DistanceMeterNonBlock::INSTANCES[1] == NULL) {
			DistanceMeterNonBlock::INSTANCES[1] = dm;
		}
		else {
			delete DistanceMeterNonBlock::INSTANCES[0];
			DistanceMeterNonBlock::INSTANCES[0] = dm;
		}
	}

	/* Static */
	void DistanceMeterNonBlock::deleteInstance(IN DistanceMeterNonBlock* dm) {
		if (DistanceMeterNonBlock::INSTANCES[0] == dm) {
			DistanceMeterNonBlock::INSTANCES[0] = NULL;
		}
		else if (DistanceMeterNonBlock::INSTANCES[1] == dm) {
			DistanceMeterNonBlock::INSTANCES[1] = NULL;
		}
	}

	/* Static */
	void DistanceMeterNonBlock::attachInterruptToInstance(IN DistanceMeterNonBlock* dm) {
		if (DistanceMeterNonBlock::INSTANCES[0] == dm) {
			attachInterrupt(digitalPinToInterrupt(dm->_echoPin), DistanceMeterNonBlock::interruptCaller0, CHANGE);
		}
		else if (DistanceMeterNonBlock::INSTANCES[1] == dm) {
			attachInterrupt(digitalPinToInterrupt(dm->_echoPin), DistanceMeterNonBlock::interruptCaller1, CHANGE);
		}
	}

	/* Static */
	void DistanceMeterNonBlock::interruptCaller0() {
		unsigned long interruptCallTimeMicros = micros();
		DistanceMeterNonBlock* temp = DistanceMeterNonBlock::INSTANCES[0];
		if (temp != NULL) {
			temp->interruptHandler(interruptCallTimeMicros);
		}
	}

	/* Static */
	void DistanceMeterNonBlock::interruptCaller1() {
		unsigned long interruptCallTimeMicros = micros();
		DistanceMeterNonBlock* temp = DistanceMeterNonBlock::INSTANCES[1];
		if (temp != NULL) {
			temp->interruptHandler(interruptCallTimeMicros);
		}
	}

	#pragma endregion

};