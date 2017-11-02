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
#include "../../GSMService.h"

#define DELAY_WAIT_FOR_DATA 200			// 200 milliseconds: Used to wait for all the data from the GSM board

#define AT_ATE0 "ATE0\r"				// Disables the command echoing 
#define AT_CNMI "AT+CNMI=2,2,0,0,0\r"	// Make GSM board send the SMS to the serial ports when received
#define AT_CMGD "AT+CMGD="				// Deletes SMS (SMS Index, [optional] flag)

#define CHAR_CTRL_Z (char)26
#define CHAR_ESC (char)27

namespace Easyuino {

	GSMService::GSMService(IN uint8_t txPin, IN uint8_t rxPin, IN Stream &outputStream)
		: GSMService(txPin, rxPin) {
		_outputStream = &outputStream;
	}

	GSMService::GSMService(IN uint8_t txPin, IN uint8_t rxPin) {
		_GSMSerial = new SoftwareSerial(txPin, rxPin);
		_outputStream = NULL;
		_isInitialized = false;
		_readyToReceiveSMS = false;
		Utilities::ZeroBuffer(_allowedNumbers, sizeof(unsigned long) * MAX_NUMBER_OF_ALLOWED_NUMBERS);
		zeroInternalBuffer();
	}

	GSMService::~GSMService() {
		end();
		delete _GSMSerial;
		_GSMSerial = NULL;
		_outputStream = NULL;
	}


	#pragma region Public GSMService API Methods

	bool GSMService::begin(IN unsigned long gsmBoardBaudRate) {
		GSMInternalRequestStatus internalTemp;

		if (!_isInitialized) {
			_GSMSerial->begin(gsmBoardBaudRate);
			_GSMSerial->print(F(AT_ATE0));		// Disables the command echo when outputing
			internalTemp = waitForGSMBoardData();

			if ((internalTemp == GSMInternalRequestStatus::GSM_INTERNAL_OK) &&
				((strcmp(_internalBuffer, AT_OK) == 0) || (strcmp(_internalBuffer, "ATE0\r\r\nOK\r\n") == 0))) {
				_isInitialized = true;
			}
			else {
				_GSMSerial->end();
				return false;
			}
		}
		return true;
	}

	bool GSMService::begin() {
		return begin(GSM_DEFAULT_BAUD_RATE);
	}

	void GSMService::end() {
		if (_isInitialized) {
			_GSMSerial->end();
			_isInitialized = false;
		}
	}

	GSMRequestStatus GSMService::addAllowedNumber(IN unsigned long numberToAdd) {
		if (numberToAdd == 0) {		// Necessary because we consider 0 not valid number
			GSMRequestStatus::GSM_REQUEST_INVALID_ARGUMENT;
		}

		for (size_t i = 0; i < MAX_NUMBER_OF_ALLOWED_NUMBERS; i++) {
			if (_allowedNumbers[i] == 0) {
				_allowedNumbers[i] = numberToAdd;
				return GSMRequestStatus::GSM_OK;
			}
		}
		return GSMRequestStatus::GSM_MAXIMUM_ALLOWED_NUMBERS_REACHED;
	}

	GSMRequestStatus GSMService::isAllowed(IN unsigned long phoneNumber, INOUT bool &allowed) {
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

	GSMRequestStatus GSMService::removeAllowedNumber(IN unsigned long phoneNumberToRemove) {
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

	GSMRequestStatus GSMService::clearAllowedNumbers() {
		Utilities::ZeroBuffer(_allowedNumbers, sizeof(unsigned long) * MAX_NUMBER_OF_ALLOWED_NUMBERS);
		return GSMRequestStatus::GSM_OK;
	}

	GSMRequestStatus GSMService::beginListenForSMS() {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		GSMInternalRequestStatus internalTemp;

		_GSMSerial->print(F(AT_CNMI));
		internalTemp = waitForGSMBoardData();

		if ((internalTemp == GSMInternalRequestStatus::GSM_INTERNAL_OK) &&
			(strcmp(_internalBuffer, AT_OK) == 0)) {
			_readyToReceiveSMS = true;
			return GSMRequestStatus::GSM_OK;
		}
		else {
			_readyToReceiveSMS = false;
			if (internalTemp == GSMInternalRequestStatus::GSM_INTERNAL_COMMUNICATION_FAILED) {
				return GSMRequestStatus::GSM_BOARD_DIDNT_REPLY;
			}
			else {
				return GSMRequestStatus::GSM_UNEXPECTED_REPLY;
			}
		}
	}

	GSMRequestStatus GSMService::availableSMS(INOUT SMS& message, OUT bool &smsRead) {
		const char delim[] = "\n";
		char *token = NULL, *next_token = NULL;
		int num_tokens = 0;

		smsRead = false;

		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		if (!_readyToReceiveSMS || !lookForGSMBoardData()) {
			return GSMRequestStatus::GSM_OK;
		}

		//Parse the SMS text in the buffer
		token = strtok_r(_internalBuffer, delim, &next_token);
		while (token != NULL) {
			if (num_tokens == 0) {
				if (strcmp(token, "\r") != 0) {
					message.reset();
					return GSMRequestStatus::GSM_OK;
				}
			}
			else if (num_tokens == 1) {
				if (strlen(token) > 20) {
					char number[10];
					Utilities::ZeroBuffer(number, 10);
					for (int i = 11; i < 20; i++) {
						number[i - 11] = token[i];
					}
					message.setNumber(atol(number));
				}
				else {
					message.reset();
					return GSMRequestStatus::GSM_OK;
				}
			}
			else if (num_tokens == 2) {
				Utilities::OverrideLastStringChar(token);
				message.setMessage(token);
			}
			else {
				message.reset();
				return GSMRequestStatus::GSM_OK;
			}

			num_tokens++;
			token = strtok_r(NULL, delim, &next_token);
		}

		if (num_tokens == 3) {
			isAllowed(message.getNumber(), smsRead);
			if (!smsRead) {
				message.reset();
			}
		}
		else {
			message.reset();
		}
		return GSMRequestStatus::GSM_OK;
	}

	GSMRequestStatus GSMService::sendSMS(IN SMS &sms) {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		GSMInternalRequestStatus internalTemp;

		zeroInternalBuffer();
		snprintf(_internalBuffer, INTERNAL_BUFFER_SIZE_BYTES - 1, "AT+CMGS=\"+%u%ld\"\r",
			sms.getCountryPrefixCode(), sms.getNumber());
		_GSMSerial->print(_internalBuffer);
		_outputStream->println(_internalBuffer);
		internalTemp = waitForGSMBoardData();

		if ((internalTemp == GSMInternalRequestStatus::GSM_INTERNAL_OK) &&
			(strcmp(_internalBuffer, "\r\n> ") == 0)) {
			_GSMSerial->print(sms.getMessage());
			_GSMSerial->print(CHAR_CTRL_Z);		// Send CTR+Z char to indicate the end of SMS
			internalTemp = waitForGSMBoardData();

			if ((internalTemp == GSMInternalRequestStatus::GSM_INTERNAL_OK) &&
				strstr(_internalBuffer, "OK") != NULL) {
				return GSMRequestStatus::GSM_OK;
			}
		}
		else {
			_GSMSerial->print(CHAR_ESC);		// Send ESC char to cancel the SMS sending
		}

		if (internalTemp == GSMInternalRequestStatus::GSM_INTERNAL_COMMUNICATION_FAILED) {
			return GSMRequestStatus::GSM_BOARD_DIDNT_REPLY;
		}
		else {
			return GSMRequestStatus::GSM_UNEXPECTED_REPLY;
		}
	}

	GSMRequestStatus GSMService::deleteAllSMS() {
		return deleteSMS(GSMSmsDeleteFlag::ALL_SMS);
	}

	GSMRequestStatus GSMService::deleteAllReadSMS() {
		return deleteSMS(GSMSmsDeleteFlag::ALL_READ_SMS);
	}

	GSMRequestStatus GSMService::deleteAllSentAndReadSMS() {
		return deleteSMS(GSMSmsDeleteFlag::ALL_SENT_AND_READ_SMS);
	}

	#pragma endregion

	#pragma region Private Methods

	GSMRequestStatus GSMService::deleteSMS(IN GSMSmsDeleteFlag flag, IN unsigned int messageIndex) {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		GSMInternalRequestStatus internalTemp;

		zeroInternalBuffer();
		snprintf(_internalBuffer, INTERNAL_BUFFER_SIZE_BYTES - 1, "%s%u,%d\r", AT_CMGD, messageIndex, flag);
		_outputStream->println(_internalBuffer);
		_GSMSerial->print(_internalBuffer);
		internalTemp = waitForGSMBoardData();

		if ((internalTemp == GSMInternalRequestStatus::GSM_INTERNAL_OK) &&
			(strcmp(_internalBuffer, AT_OK) == 0)) {
			return GSMRequestStatus::GSM_OK;
		}
		else if (internalTemp == GSMInternalRequestStatus::GSM_INTERNAL_COMMUNICATION_FAILED) {
			return GSMRequestStatus::GSM_BOARD_DIDNT_REPLY;
		}
		else {
			return GSMRequestStatus::GSM_UNEXPECTED_REPLY;
		}
	}

	GSMService::GSMInternalRequestStatus GSMService::waitForGSMBoardData() {
		unsigned long waitInitTime = millis();
		while (_GSMSerial->available() == 0) {
			/* ACTIVELY wait for data */
			if ((millis() - waitInitTime) > WAIT_FOR_DATA_TIMEOUT) {  // TIMEOUT - Waiting for board reply
				return GSM_INTERNAL_COMMUNICATION_FAILED;
			}
		}
		lookForGSMBoardData();
		return GSM_INTERNAL_OK;
	}

	bool GSMService::lookForGSMBoardData() {
		int count = 0;

		if (_GSMSerial->available() > 0) {
			zeroInternalBuffer();
			delay(DELAY_WAIT_FOR_DATA);

			while (_GSMSerial->available() > 0) {
				_internalBuffer[count++] = _GSMSerial->read();
				if (count == (INTERNAL_BUFFER_SIZE_BYTES - 1)) {
					break;
				}
			}

			if (_outputStream != NULL) {	//Output the GSM board output if user want
				_outputStream->write(_internalBuffer, count);
			}

			return true;
		}
		else {
			return false;
		}
	}

	void GSMService::zeroInternalBuffer() {
		Utilities::ZeroBuffer(_internalBuffer, INTERNAL_BUFFER_SIZE_BYTES);
	}

	#pragma endregion


};