#include "../../DistanceMeter.h"

#define MAX_UNSIGNED_LONG 4294967295

#define ECHO_TIMEOUT_MICROS 2000000			// 2 seconds
#define SOUND_SPEED_CM_PER_SEC 340000.0f	// Sound speed in air at 15 Celsius

namespace Easyuino {

	DistanceMeter* DistanceMeter::singleton;

	DistanceMeter::DistanceMeter(uint8_t triggerPin, uint8_t echoPin) : Device() {
		_triggerPin = triggerPin;
		_echoPin = echoPin;
		_timeTrigger = -1;
		_distance = -1;
		_isEchoing = false;
		_echoSent = false;
		_blockingMeasure = true;
		_isDirtyDistance = true;
		if (DistanceMeter::singleton != NULL) {
			delete DistanceMeter::singleton;
		}
		DistanceMeter::singleton = this;
	}

	DistanceMeter::~DistanceMeter() {
		DistanceMeter::singleton = NULL;
	}

	void DistanceMeter::InterruptCaller() {
		DistanceMeter::singleton->interruptHandler();
	}

	void DistanceMeter::begin() {
		if (!_isInitialized) {
			pinMode(_triggerPin, OUTPUT);
			pinMode(_echoPin, INPUT);
			digitalWrite(_echoPin, LOW);
			_isInitialized = true;
			attachInterrupt(digitalPinToInterrupt(_echoPin), DistanceMeter::InterruptCaller, CHANGE);
		}
	}

	void DistanceMeter::end() {
		if (_isInitialized) {
			_isInitialized = false;
			_isEchoing = false;
			_echoSent = false;
			_blockingMeasure = true;
			_isDirtyDistance = true;
			_timeTrigger = -1;
			_distance = -1;
			detachInterrupt(digitalPinToInterrupt(_echoPin));
		}
	}

	float DistanceMeter::getDistance() {
		// Micro timer overflow detected returning last one we had OR the value stored is the most recent we have
		if (!_isDirtyDistance || (_lastTimeEcho < _lastTimeTrigger)) {
			return _distance;
		}
		else {
			_distance = ((_lastTimeEcho - _lastTimeTrigger) * SOUND_SPEED_CM_PER_SEC) / 2000000.0f;
			_isDirtyDistance = false;
			return _distance;
		}
	}

	void DistanceMeter::updateDistanceBlock() {
		if (_isInitialized) {
			if (!_isEchoing) {	// Don't allow block measure while a non-blocking on is on going
				_blockingMeasure = true;
				digitalWrite(_triggerPin, LOW);
				delayMicroseconds(2);
				digitalWrite(_triggerPin, HIGH);
				delayMicroseconds(10);
				digitalWrite(_triggerPin, LOW);
				delayMicroseconds(2);
				_distance = (pulseIn(_echoPin, HIGH, ECHO_TIMEOUT_MICROS) * SOUND_SPEED_CM_PER_SEC / 2000000.0f);
				_isDirtyDistance = false;
			}
			else {
				if (micros() - _timeTrigger > ECHO_TIMEOUT_MICROS) {	// Timeout for the non-block echo detected
					_echoSent = _isEchoing = false;
					updateDistanceBlock();
				}
			}
		}
	}

	void DistanceMeter::updateDistanceNonBlock() {
		if (_isInitialized) {
			if (!_isEchoing) {
				_blockingMeasure = false;
				_isEchoing = true;
				digitalWrite(_triggerPin, LOW);
				delayMicroseconds(2);
				digitalWrite(_triggerPin, HIGH);
				delayMicroseconds(10);
				digitalWrite(_triggerPin, LOW);
				delayMicroseconds(2);
			}
			else {
				if (micros() - _timeTrigger > ECHO_TIMEOUT_MICROS) {	// Timeout for the non-block echo detected
					_echoSent = _isEchoing = false;
					updateDistanceNonBlock();
				}
			}
		}
	}

	#pragma region Private Methods


	void DistanceMeter::interruptHandler() {
		unsigned long currentTime = micros();
		if (!_blockingMeasure) {
			if (digitalRead(_echoPin) == HIGH && _isEchoing && !_echoSent) {
				_timeTrigger = currentTime;
				_echoSent = true;
			}
			else if (digitalRead(_echoPin) == LOW && _isEchoing && _echoSent) {
				 _isEchoing = _echoSent = false;
				 _isDirtyDistance = true;
				_lastTimeTrigger = _timeTrigger;
				_lastTimeEcho = currentTime;
			}
		}
	}

	#pragma endregion

};