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

#define DELAY_WAIT_FOR_DATA 200						// 200 milliseconds: Used to wait for all the data from the GSM module
#define WAIT_FOR_DATA_TIMEOUT 5000					// 5 seconds

#define AT_COMM_DISABLE_ECHOING "ATE0\r"			// Disables the command echoing 
#define AT_COMM_SMS_TO_SERIAL "AT+CNMI=2,2,0,0,0\r"	// Make GSM module send the SMS to the serial ports when received
#define AT_COMM_DELETE_SMS "AT+CMGD="				// Deletes SMS (SMS Index, [optional] flag)
#define AT_COMM_MANUFACTER_ID "AT+CGMI=?\r"			// Used only yo know if the module is on or off
#define AT_COMM_SET_BAUD_RATE "AT+IPR="				// Used to set the baud rate of the GSM module

#define CHAR_CTRL_Z (char)26
#define CHAR_ESC (char)27

namespace Easyuino {

	GSMService::GSMService(IN uint8_t txPin, IN uint8_t rxPin, IN uint8_t powerPin, IN Stream &outputStream)
		: GSMService(txPin, rxPin, powerPin) {
		_outputStream = &outputStream;
	}

	GSMService::GSMService(IN uint8_t txPin, IN uint8_t rxPin, IN uint8_t powerPin)  
		: Device() {
		_GSMSerial = new SoftwareSerial(txPin, rxPin);
		_powerPin = powerPin;
		_outputStream = NULL;
		_readyToReceiveSMS = false;
		zeroInternalBuffer();
	}

	GSMService::~GSMService() {
		end();
		delete _GSMSerial;
	}

#pragma region Public GSMService API Methods

	bool GSMService::begin(IN unsigned long gsmmoduleBaudRate) {
		if (!_isInitialized) {
			_GSMSerial->begin(gsmmoduleBaudRate);
			pinMode(_powerPin, OUTPUT);
			_isInitialized = true;
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

	GSMRequestStatus GSMService::turnOn() {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		GSMRequestStatus internalReq;
		bool on;
		internalReq = isOn(on);
		if (internalReq == GSMRequestStatus::GSM_OK && !on) {
			digitalWrite(_powerPin, LOW);
			delay(1000);
			digitalWrite(_powerPin, HIGH);
			delay(2000);
			digitalWrite(_powerPin, LOW);
			delay(1000);
			delay(GSM_DELAY_NETWORK_LOGIN);	//Delay to log in in the network

			lookForGSMmoduleData();	// Discard turn on data
		}
		return internalReq;
	}

	GSMRequestStatus GSMService::turnOff() {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		GSMRequestStatus internalReq;
		bool on;
		internalReq = isOn(on);
		if (internalReq == GSMRequestStatus::GSM_OK && on) {
			digitalWrite(_powerPin, LOW);
			delay(1000);
			digitalWrite(_powerPin, HIGH);
			delay(2000);
			digitalWrite(_powerPin, LOW);
			delay(1000);
		}
		return internalReq;
	}

	GSMRequestStatus GSMService::isOn(OUT bool &isOn) {
		if (!_isInitialized) {
			isOn = false;
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		GSMRequestStatus internalReq;
		isOn = false;

		_GSMSerial->print(F(AT_COMM_MANUFACTER_ID));
		internalReq = waitForGSMmoduleData();

		if (internalReq == GSMRequestStatus::GSM_OK) {
			if (strlen(_internalBuffer) > 0) {
				isOn = true;
			}
		}
		return GSMRequestStatus::GSM_OK;
	}

	GSMRequestStatus GSMService::setBaudRate(IN unsigned long newBaudRate) {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		GSMRequestStatus internalReq;

		_GSMSerial->print(F(AT_COMM_SET_BAUD_RATE));
		_GSMSerial->print(newBaudRate);
		_GSMSerial->print('\r');
		internalReq = waitForGSMmoduleData();

		if (internalReq == GSMRequestStatus::GSM_OK) {
			if (strcmp(_internalBuffer, AT_OK) == 0) {
				_GSMSerial->end();
				_GSMSerial->begin(newBaudRate);
				return GSMRequestStatus::GSM_OK;
			}
			else {
				return GSMRequestStatus::GSM_UNEXPECTED_REPLY;
			}
		}
		else {
			return internalReq;
		}
	}

	GSMRequestStatus GSMService::beginListenForSMS() {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		GSMRequestStatus internalReq;

		_readyToReceiveSMS = false;

		_GSMSerial->print(F(AT_COMM_SMS_TO_SERIAL));
		internalReq = waitForGSMmoduleData();

		if ((internalReq == GSMRequestStatus::GSM_OK)) {
			if (strcmp(_internalBuffer, AT_OK) == 0) {
				_readyToReceiveSMS = true;
				return GSMRequestStatus::GSM_OK;
			}
			else {
				return GSMRequestStatus::GSM_UNEXPECTED_REPLY;
			}
		}
		else {
			return internalReq;
		}
	}

	GSMRequestStatus GSMService::availableSMS(OUT SMS& message, OUT bool &smsRead) {
		const char delim[] = "\n";
		char *token = NULL, *next_token = NULL;
		int num_tokens = 0;

		smsRead = false;

		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		if (!_readyToReceiveSMS || !lookForGSMmoduleData()) {
			return GSMRequestStatus::GSM_OK;
		}

		//Parse the SMS text in the buffer
		token = strtok_r(_internalBuffer, delim, &next_token);
		while (token != NULL) {
			if (num_tokens == 0) {
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
			else if (num_tokens == 1) {
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

		if(num_tokens != 2) {
			message.reset();
		}
		else {
			smsRead = true;
		}

		return GSMRequestStatus::GSM_OK;
	}

	GSMRequestStatus GSMService::getUnreadSMS(INOUT SMS &sms, OUT bool &smsAvailable) {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		GSMRequestStatus internalReq;
		unsigned int countryPrefixCode = 0;
		unsigned long phoneNumber = 0;
		char* messageContentPtr = NULL;
		int ctr = 0;
		smsAvailable = false;

		_GSMSerial->print(F("AT+CMGL=\"REC READ\"\r"));
		internalReq = waitForGSMmoduleData();

		if (internalReq == GSMRequestStatus::GSM_OK) {
			if (strcmp(_internalBuffer, AT_OK) == 0) {
				Serial.println("No Unread Messages");
				return GSMRequestStatus::GSM_OK;
			}
			else {
				Serial.println("Unread Messages");
				while (_internalBuffer[ctr] != '\n') {	// Looking in the message header
					bool insideField = false;

					if (_internalBuffer[ctr] == '"' && _internalBuffer[ctr+1] == '+') {	// Phone number found
						int countryCounter = 0;
						ctr = ctr + 2;
						while (_internalBuffer[ctr] != '"') {
							if (countryCounter < 3) {
								countryPrefixCode = (countryPrefixCode * 10) + (_internalBuffer[ctr] - '0');
								countryCounter++;
							}
							else {
								phoneNumber = (phoneNumber * 10) + (_internalBuffer[ctr] - '0');
							}
							ctr++;
						}
						continue;
					}

					ctr++;
				}
				messageContentPtr = _internalBuffer + (sizeof(char) * ++ctr);
				while (_internalBuffer[ctr] != '\r') {	// Looking in the message content
					ctr++;
				}
				_internalBuffer[ctr] = '\0';
			}
			if (phoneNumber != 0) {	// Make sure we read a messages and not junk
				smsAvailable = true;
				sms.setNumber(phoneNumber);
				sms.setCountryPrefixCode(countryPrefixCode);
				sms.setMessage(messageContentPtr);
			}
		}
		return internalReq;
	}

	GSMRequestStatus GSMService::sendSMS(IN SMS &sms) {
		if (!_isInitialized) {
			return GSMRequestStatus::NOT_INITIALIZED;
		}
		GSMRequestStatus internalReq;

		zeroInternalBuffer();
		snprintf(_internalBuffer, INTERNAL_BUFFER_SIZE_BYTES - 1, "AT+CMGS=\"+%u%ld\"\r",
			sms.getCountryPrefixCode(), sms.getNumber());
		_GSMSerial->print(_internalBuffer);
		_outputStream->println(_internalBuffer);
		internalReq = waitForGSMmoduleData();

		if ((internalReq == GSMRequestStatus::GSM_OK) &&
			(strcmp(_internalBuffer, "\r\n> ") == 0)) {
			_GSMSerial->print(sms.getMessage());
			_GSMSerial->print(CHAR_CTRL_Z);		// Send CTR+Z char to indicate the end of SMS
			internalReq = waitForGSMmoduleData();

			if ((internalReq == GSMRequestStatus::GSM_OK) &&
				strstr(_internalBuffer, "OK") != NULL) {
				return GSMRequestStatus::GSM_OK;
			}
		}
		else {
			_GSMSerial->print(CHAR_ESC);		// Send ESC char to cancel the SMS sending
		}

		if (internalReq == GSMRequestStatus::GSM_MODULE_DIDNT_REPLY) {
			return GSMRequestStatus::GSM_MODULE_DIDNT_REPLY;
		}
		else {
			return GSMRequestStatus::GSM_UNEXPECTED_REPLY;
		}
	}

	GSMRequestStatus GSMService::sendSMS(IN unsigned long phoneNumber, IN const char* message, IN unsigned int countryPrefixCode) {
		SMS smsToSend = SMS(phoneNumber, message, countryPrefixCode);
		return sendSMS(smsToSend);
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
		GSMRequestStatus internalReq;

		zeroInternalBuffer();
		snprintf(_internalBuffer, INTERNAL_BUFFER_SIZE_BYTES - 1, "%s%u,%d\r", AT_COMM_DELETE_SMS, messageIndex, flag);
		_outputStream->println(_internalBuffer);
		_GSMSerial->print(_internalBuffer);
		internalReq = waitForGSMmoduleData();

		if ((internalReq == GSMRequestStatus::GSM_OK)) {
			if (strcmp(_internalBuffer, AT_OK) == 0) {
				return GSMRequestStatus::GSM_OK;
			}
			else {
				return GSMRequestStatus::GSM_UNEXPECTED_REPLY;
			}
		}
		else {
			return internalReq;
		}
	}

	GSMRequestStatus GSMService::waitForGSMmoduleData() {
		unsigned long waitInitTime = millis();
		while (_GSMSerial->available() == 0) {
			/* ACTIVELY wait for data */
			if ((millis() - waitInitTime) > WAIT_FOR_DATA_TIMEOUT) {  // TIMEOUT - Waiting for module reply
				return GSMRequestStatus::GSM_MODULE_DIDNT_REPLY;
			}
		}
		lookForGSMmoduleData();
		return GSMRequestStatus::GSM_OK;
	}

	bool GSMService::lookForGSMmoduleData() {
		int count = 0;

		if (_GSMSerial->available() > 0) {
			zeroInternalBuffer();
			delay(DELAY_WAIT_FOR_DATA);

			while (_GSMSerial->read() != '\n');	// Discard the first line that normally is command echo

			while (_GSMSerial->available() > 0) {	// Fill the API buffer with the data from the module
				_internalBuffer[count++] = _GSMSerial->read();
				if (count == (INTERNAL_BUFFER_SIZE_BYTES - 1)) {
					break;
				}
			}

			if (_outputStream != NULL) {		//Output the GSM module output if debug serial is defined
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