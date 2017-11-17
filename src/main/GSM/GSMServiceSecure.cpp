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
#include "../../GSMServiceSecure.h"

namespace Easyuino {
	
	GSMServiceSecure::GSMServiceSecure(IN uint8_t txPin, IN uint8_t rxPin, IN uint8_t powerPin, IN Stream & outputStream)
	: GSMService(txPin, rxPin, powerPin, outputStream) {
		Utilities::ZeroBuffer(_allowedNumbers, sizeof(unsigned long) * MAX_NUMBER_OF_ALLOWED_NUMBERS);
	}

	GSMServiceSecure::GSMServiceSecure(IN uint8_t txPin, IN uint8_t rxPin, IN uint8_t powerPin)
	: GSMService(txPin, rxPin, powerPin) {
		Utilities::ZeroBuffer(_allowedNumbers, sizeof(unsigned long) * MAX_NUMBER_OF_ALLOWED_NUMBERS);
	}

	GSMServiceSecure::~GSMServiceSecure() { /* Do Nothing */ }

	GSMRequestStatus GSMServiceSecure::addAllowedNumber(IN unsigned long phoneNumberToAdd) {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		if (phoneNumberToAdd == 0) {		// Necessary because we consider 0 not valid number
			return GSMRequestStatus::GSM_REQUEST_INVALID_ARGUMENT;
		}

		for (size_t i = 0; i < MAX_NUMBER_OF_ALLOWED_NUMBERS; i++) {
			if (_allowedNumbers[i] == 0) {
				_allowedNumbers[i] = phoneNumberToAdd;
				return GSMRequestStatus::GSM_OK;
			}
		}
		return GSMRequestStatus::GSM_MAXIMUM_ALLOWED_NUMBERS_REACHED;
	}

	GSMRequestStatus GSMServiceSecure::isAllowed(IN unsigned long phoneNumber, OUT bool & allowed) {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		if (phoneNumber == 0) {		// Necessary because we consider 0 not valid number
			allowed = false;
			return GSMRequestStatus::GSM_REQUEST_INVALID_ARGUMENT;
		}
		allowed = true;

		for (size_t i = 0; i < MAX_NUMBER_OF_ALLOWED_NUMBERS; i++) {
			if (_allowedNumbers[i] == phoneNumber) {
				allowed = true;
				break;
			}
			else if (_allowedNumbers[i] != 0) {
				allowed = false;
			}
		}
		return GSMRequestStatus::GSM_OK;
	}

	GSMRequestStatus GSMServiceSecure::removeAllowedNumber(IN unsigned long phoneNumberToRemove) {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		if (phoneNumberToRemove == 0) {		// Necessary because we consider 0 not valid number
			return GSMRequestStatus::GSM_REQUEST_INVALID_ARGUMENT;
		}

		for (size_t i = 0; i < MAX_NUMBER_OF_ALLOWED_NUMBERS; i++) {
			if (_allowedNumbers[i] == phoneNumberToRemove) {
				_allowedNumbers[i] = 0;
				break;
			}
		}
		return GSMRequestStatus::GSM_OK;
	}

	GSMRequestStatus GSMServiceSecure::clearAllowedNumbers() {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		Utilities::ZeroBuffer(_allowedNumbers, sizeof(unsigned long) * MAX_NUMBER_OF_ALLOWED_NUMBERS);
		return GSMRequestStatus::GSM_OK;
	}

	GSMRequestStatus GSMServiceSecure::availableSMS(INOUT SMS & message, OUT bool & smsRead) {
		GSMRequestStatus requestRes = GSMService::availableSMS(message, smsRead);
		if (requestRes != GSMRequestStatus::NOT_INITIALIZED) {
			isAllowed(message.getNumber(), smsRead);
			if (!smsRead) {
				message.reset();
			}
		}
		return requestRes;
	}

};