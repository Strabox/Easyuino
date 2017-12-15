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
/*
GSMService.h
*/
#ifndef _EASYUINO_GSM_SERVICE_h
#define _EASYUINO_GSM_SERVICE_h

#include <SoftwareSerial.h>
#include "Utilities.h"
#include "Device.h"
#include "SMS.h"

/** Delay for login in the network after turning on the module (Default 10 Seconds) */
#define GSM_DELAY_NETWORK_LOGIN 10000	
/** It can change depending on the module (Default) */
#define GSM_DEFAULT_BAUD_RATE 9600

/** 
IMPORTANT: Size (bytes) of the buffer used internally to receive/send data from/to the GSM module
if you have more memory you can change this (Advisable to change if you will receive huge SMSs)
*/
#define INTERNAL_BUFFER_SIZE_BYTES 128

namespace Easyuino {

	/** Used to indicate the status of the request to the GSMService API */
	enum class GSMRequestStatus : uint8_t {
		/** The request was successful executed by the GSMService API */
		GSM_OK = 0,
		/** Happens in many cases where the module answer with things we were not expected due to:
		- Error in our API (e.g: invalid inputs to the GSMService API that we let pass to the module).
		- Defect in the module or a general hardware error (not likely).
		IMPORTANT: In this case we consider the request failed and you should repeat the request.
		*/
		GSM_UNEXPECTED_REPLY = 1,
		/** GSMService API tried communicate with the GSM module and it didn't answer in reasonable time
		(e.g: when module is turned off, when module hardware is broken)
		*/
		GSM_MODULE_DIDNT_REPLY = 2,
		/** When provided an invalid argument to the GSMService API (e.g: invalid pin number, invalid baud rate, ...) */
		GSM_REQUEST_INVALID_ARGUMENT = 4,
		/** Not possible add more allowed numbers to the GSMService API */
		GSM_MAXIMUM_ALLOWED_NUMBERS_REACHED = 5,
		/** The GSMService API was not correctly initialized and can't process requests */
		NOT_INITIALIZED = 255
	};

	/** GSMService API allows to interact with GSM boards in order to perform calls, sms management etc.
	@see Devices Supported:		SIM90x Series Chipset, SIM80x Chipset
	@see Devices Tested:		SIM900 Chipset
	*/
	class GSMService : public Device {

	private:
		/** Indicate what type and amount of stored SMSs we want to delete (See AT Commands Reference) */
		enum GSMSmsDeleteFlag : uint8_t {
			INDEX_PARAMTER_CHOSEN_ONLY = 0,
			ALL_READ_SMS = 1,
			ALL_SENT_AND_READ_SMS = 2,
			ALL_SMS = 3
		};

		const char *AT_OK = "OK\r\n";
		const char *AT_ERROR = "ERROR\r\n";

		/** Arduino pin that is connected to the power pin of the GSM module */
		uint8_t _powerPin;

		/** Debug Stream used to output the RAW output of the GSM module (Used for debugging purposes only) */
		Stream*_outputStream;
		
		/** Software serial object that uses (tx pin and rx pin) to interact with the GSM module */
		SoftwareSerial* _GSMSerial;

		/** Buffer used internally to receive/send data from/to the GSM module */
		char _internalBuffer[INTERNAL_BUFFER_SIZE_BYTES];

		/** Used to know if the module is "spitting" the SMS to the serial or not */
		bool _readyToReceiveSMS;

	public:
		/** Constructor
		@param txPin		Arduino pin used to send the serial information to GSM module
		@param rxPin		Arduino pin used to receive the serial information from GSM module
		@param powerPin		Arduino pin used to turn on and off the GSM module
		@param outputStream	Debug output stream
		*/
		GSMService(IN uint8_t txPin, IN uint8_t rxPin, IN uint8_t powerPin, IN Stream &outputStream);

		/** Constructor
		@param txPin	Arduino pin used to send the serial information to GSM module
		@param rxPin	Arduino pin used to receive the serial information from GSM module
		@param powerPin	Arduino pin used to turn on and off the GSM module
		*/
		GSMService(IN uint8_t txPin, IN uint8_t rxPin, IN uint8_t powerPin);

		/** Destructor */
		~GSMService();

		/** Initialize the GSMService API make it ready tor receive requests
		@param gsmModuleBaudRate	Baud rate to communicate with the GSM module
		@return						True: If begin was success. False: Otherwise.
		*/
		bool begin(IN unsigned long gsmModuleBaudRate);

		/** Initialize the GSMService API make it ready tor receive requests
		It uses the baud rate GSM_DEFAULT_BAUD_RATE to initialize the API.
		@return	True: If begin was success. False: Otherwise.
		*/
		bool begin();

		/** Stops the GSMService API making it unable to receive more requests */
		void end();

#pragma region GSM Physical Module Management

		/** Turns On the GSM module if it is turned Off.
		@return	GSMRequestStatus (NOT_INITIALIZED, GSM_OK)
		*/
		GSMRequestStatus turnOn();

		/** Turns Off the GSM module if it is turned On.
		@return	GSMRequestStatus (NOT_INITIALIZED, GSM_OK)
		*/
		GSMRequestStatus turnOff();

		/** Used to see if the GSM module is turned on or off.
		@param isOn					True: If GSM board is on. False: otherwise.
		@return	GSMRequestStatus	(NOT_INITIALIZED, GSM_OK)
		*/
		GSMRequestStatus isOn(OUT bool &isOn);

		/** Set the baud rate of the GSM module to a new one.
		After calling this method with success the next time you use the GSM module
		you need to provide this new baud rate in the begin(unsigned long) method.
		@param newBaudRate			New baud rate to communicate with the GSM module.
		@return	GSMRequestStatus	(NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus setBaudRate(IN unsigned long newBaudRate);

#pragma endregion

#pragma region SMS Management

		/** Start listening for SMS reception. Necessary for the availableSMS() return new SMSs.
		@return	GSMRequestStatus (NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus beginListenForSMS();

		/** Check if there is a new received SMS. If there is it filles the message with the content.
		@param message				Message reference to be filled by the method if there is a new SMS.
		@param smsRead				Filled by the API. True: if a SMS was available. False: otherwise.
		@return	GSMRequestStatus	(NOT_INITIALIZED, GSM_OK)
		*/
		virtual GSMRequestStatus availableSMS(OUT SMS &message, OUT bool &smsRead);

		/** Send a SMS through the GSM module.
		@param sms					Reference of the the filled SMS to be sent by the GSM module.
		@return	GSMRequestStatus	(NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus sendSMS(IN SMS &sms);

		/** Send a SMS through the GSM module.
		@param phoneNumber			Phone number of SMS receipt.
		@param message				The message content to be sent.
		@param countryPrefixCode	The country prefix code of the phone number.
		@return	GSMRequestStatus	(NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus sendSMS(IN unsigned long phoneNumber, IN const char* message, IN unsigned int countryPrefixCode);

		/** Delete all the sms in the GSM module.
		@return	GSMRequestStatus (NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus deleteAllSMS();

		/** Detele all the messages that were received and read.
		@return	GSMRequestStatuss (NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus deleteAllReadSMS();

		/** Delete all the the messages that were received and read plus the sent ones.
		@return	GSMRequestStatus (NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus deleteAllSentAndReadSMS();

#pragma endregion 

	private:
		/** Get unread messages without the need to make the board spit incoming messages to the serial.
		@Unreleased to public for now!
		*/
		GSMRequestStatus getUnreadSMS(INOUT SMS &sms, OUT bool &smsAvailable);

		/** Delete SMS depending on the flags passed to the method.
		@param parameter			Parameter passed to AT delete SMS command
		@param messageIndex			Index message to delete if it is to delete a specific one
		@return	GSMRequestStatus	(NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus deleteSMS(IN GSMSmsDeleteFlag parameter, IN unsigned int messageIndex = 0);

		/** Actively waits for data from the GSM module. After WAIT_FOR_DATA_TIMEOUT it gives up.
		@return	GSMRequestStatus (GSM_OK, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus waitForGSMmoduleData();

		/** Verify if there are information from the GSM module waiting in the SoftwareSerial.
		@return True: If there was data from the GSM module waiting. False: Otherwise.
		*/
		bool lookForGSMmoduleData();

		/** Zero the interal buffer of the library. Normally used before receive data or before using
		the buffer to manage strings.
		*/
		void zeroInternalBuffer();

	};

};

#endif
