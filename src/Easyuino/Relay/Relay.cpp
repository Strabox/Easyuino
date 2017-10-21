#include "../../Relay.h"

namespace Easyuino {

	Relay::Relay(uint8_t arduinoPin) : Device() {
		_arduinoPin = arduinoPin;
		_isOpen = false;
	}

	Relay::~Relay() { /* Do Nothing */ }

	void Relay::begin() {
		begin(HIGH);	// Default is HIGH
	}

	void Relay::begin(uint8_t closedStatePinLevel) {
		if (!_isInitialized && (closedStatePinLevel == LOW || closedStatePinLevel == HIGH)) {
			pinMode(_arduinoPin, OUTPUT);
			digitalWrite(_arduinoPin, closedStatePinLevel);
			_isInitialized = true;
		}
	}

	void Relay::end() {
		if (_isInitialized) {
			close();
			_isInitialized = false;
		}
	}

	void Relay::open() {
		if (_isInitialized && !_isOpen) {
			if (digitalRead(_arduinoPin) == HIGH) {
				digitalWrite(_arduinoPin, LOW);
			}
			else {
				digitalWrite(_arduinoPin, HIGH);
			}
			_isOpen = true;
		}
	}

	void Relay::close() {
		if (_isInitialized && _isOpen) {
			if (digitalRead(_arduinoPin) == HIGH) {
				digitalWrite(_arduinoPin, LOW);
			}
			else {
				digitalWrite(_arduinoPin, HIGH);
			}
			_isOpen = false;
		}
	}

	bool Relay::isOpen() const {
		return _isOpen;
	}

};