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

/* Delay for login in the network after turning on the module (Default 10 seconds) */
#define GSM_DELAY_NETWORK_LOGIN 10000	
/* It can change depending on the module (Default) */
#define GSM_DEFAULT_BAUD_RATE 9600

/* 
IMPORTANT: Size (bytes) of the buffer used internally to receive/send data from/to the GSM module
if you have more memory you can change this (Advisable to change if you will receive huge SMSs)
*/
#define INTERNAL_BUFFER_SIZE_BYTES 128
/* IMPORTANT: Maximum number of allowed numbers to do CALLS and send SMS to the module */
#define MAX_NUMBER_OF_ALLOWED_NUMBERS 3

namespace Easyuino {

	/* Used to indicate the status of the request to the GSMService API */
	enum class GSMRequestStatus : uint8_t {
		/* The request was successful executed by the GSMService API */
		GSM_OK = 0,
		/* 
		Happens in many cases where the module answer with things we were not expected due to:
		- Error in our API (e.g: invalid inputs to the GSMService API that we let pass to the module).
		- Defect in the module or a general hardware error (not likely).
		IMPORTANT: In this case we consider the request failed and you should repeat the request.
		*/
		GSM_UNEXPECTED_REPLY = 1,
		/* 
		GSMService API tried communicate with the GSM module and it didn't answer in reasonable time
		(e.g: module is turned off, module HW is broken)
		*/
		GSM_MODULE_DIDNT_REPLY = 2,
		/* When provided an invalid argument to the GSMService API (e.g: negative pin number, negative baud rate, ...) */
		GSM_REQUEST_INVALID_ARGUMENT = 4,
		/* Not possible add more allowed numbers to the GSMService API */
		GSM_MAXIMUM_ALLOWED_NUMBERS_REACHED = 5,
		/* The GSMService API was not correctly initialized and can't process requests */
		NOT_INITIALIZED = 255
	};

	/*
	Implementation of a GSMService API to interact with the GSM modules.
	@Physical Devices Supported:
	- SIM90x Series Chipset, SIM80x Chipset
	@Physical Devices Tested:
	- SIM900 Chipset
	*/
	class GSMService : public Device {

	private:
		/* Indicate what type and amount of stored SMSs we want to delete (See AT Commands Reference) */
		enum GSMSmsDeleteFlag : uint8_t {
			INDEX_PARAMTER_CHOSEN_ONLY = 0,
			ALL_READ_SMS = 1,
			ALL_SENT_AND_READ_SMS = 2,
			ALL_SMS = 3
		};

		const char *AT_OK = "OK\r\n";
		const char *AT_ERROR = "ERROR\r\n";

		/* Arduino pin that is connected to the power pin of the GSM module */
		uint8_t _powerPin;

		/* Debug Stream used to output the RAW output of the GSM module (Debugging purposes mostly) */
		Stream*_outputStream;
		
		/* Software serial object that uses (tx pin and rx pin) to interact with the GSM module */
		SoftwareSerial* _GSMSerial;

		/* Buffer used internally to receive/send data from/to the GSM module */
		char _internalBuffer[INTERNAL_BUFFER_SIZE_BYTES];

		/* Used to know if the module is "spitting" the SMS to the serial or not */
		bool _readyToReceiveSMS;

	public:
		/*
		Creates a GSMService API object.
		@param txPin		- Pin used to send the serial information to GSM module
		@param rxPin		- Pin used to receive the serial information from GSM module
		@param powerPin		- Pin used to turn on and off the GSM module
		@param outputStream	- Stream to output the GSM module raw data
		*/
		GSMService(IN uint8_t txPin, IN uint8_t rxPin, IN uint8_t powerPin, IN Stream &outputStream);

		/*
		Creates a GSMService API object.
		@param txPin	- Pin used to send the serial information to GSM module
		@param rxPin	- Pin used to receive the serial information from GSM module
		@param powerPin	- Pin used to turn on and off the GSM module
		*/
		GSMService(IN uint8_t txPin, IN uint8_t rxPin, IN uint8_t powerPin);

		/* Deallocates all the internal resources used by the GSMService */
		~GSMService();

		/*  
		Initialize the GSMService API make it ready tor receive requests.
		@param gsmmoduleBaudRate	- Baud rate to talk with the GSM module
		@return						- True: If begin was success. False: Otherwise.
		*/
		bool begin(IN unsigned long gsmModuleBaudRate);

		/*
		Initialize the GSMService API make it ready tor receive requests.
		It uses the baud rate GSM_DEFAULT_BAUD_RATE to initialize the API.
		@return						- True: If begin was success. False: Otherwise.
		*/
		bool begin();

		/*
		Stops the GSMService API. If you want send requests to it again you must call begin.
		*/
		void end();

#pragma region GSM Physical Module Management

		/*
		Turns On the GSM module if it is turned Off.
		@return	- GSMService API request status (NOT_INITIALIZED, GSM_OK)
		*/
		GSMRequestStatus turnOn();

		/*
		Turns Off the GSM module if it is turned On.
		@return	- GSMService API request status (NOT_INITIALIZED, GSM_OK)
		*/
		GSMRequestStatus turnOff();

		/*
		Used to see if the GSM module is turned On or not.
		@param result	- A boolean variable that is set to true if is on and false otherwise.
		@return			- GSMService API request status (NOT_INITIALIZED, GSM_OK)
		*/
		GSMRequestStatus isOn(OUT bool &result);

		/*
		Set the baud rate of the GSM module to a new value.
		ATTENTION: After calling this method with success the next time you use the GSM module
		you need to provide this new baud rate that was defined.
		@param newBaudRate	- New baud rate to talk with the GSM module.
		@return				- GSMService API request status (NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus setBaudRate(IN unsigned long newBaudRate);

#pragma endregion

#pragma region SMS Management

		/*
		Start listening for SMS reception. Necessary to the availableSMS method SMS detection.
		@return	- GSMService API request status (NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus beginListenForSMS();

		/*
		Check if there is a new received SMS.
		@param message	- Message reference to be filled by the method if there is a new SMS.
		@param smsRead	- Filled by the API. True if a SMS was available. False otherwise.
		@return			- GSMService API request status (NOT_INITIALIZED, GSM_OK)
		*/
		virtual GSMRequestStatus availableSMS(OUT SMS &message, OUT bool &smsRead);

		/*
		Send a SMS through the GSM module.
		@param sms	- Reference to the the SMS to be sent by the GSM module.
		@return		- GSMService API request status (NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus sendSMS(IN SMS &sms);

		/*
		Send a SMS through the GSM module.
		@param phoneNumber		- Phone number of SMS receipt.
		@param message			- The message to be sent.
		@param countryPrefixCode- The country prefix code of the phone numbers.
		@return					- GSMService API request status (NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus sendSMS(IN unsigned long phoneNumber, IN const char* message, IN unsigned int countryPrefixCode);

		/*
		Delete all the sms in the GSM module.
		@return	- GSMService API request status (NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus deleteAllSMS();

		/*
		Detele all the messages that were received and read.
		@return	- GSMService API request status (NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus deleteAllReadSMS();

		/*
		Delete all the the messages that were received and read plus the sent ones.
		@return	- GSMService API request status (NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus deleteAllSentAndReadSMS();

#pragma endregion 

	private:
		
		/*
		Get unread messages without the need to make the board spit incoming messages to the serial-
		@Unreleased in public for now!
		*/
		GSMRequestStatus getUnreadSMS(INOUT SMS &sms, OUT bool &smsAvailable);

		/*
		Delete SMS depending on the flags passed to the method.
		@param parameter	- Parameter passed to AT delete SMS command
		@param messageIndex	- Index message to delete if it is to delete a specific one
		@return				- GSMService API request status (NOT_INITIALIZED, GSM_OK, GSM_UNEXPECTED_REPLY, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus deleteSMS(IN GSMSmsDeleteFlag parameter, IN unsigned int messageIndex = 0);

		/*
		Actively waits for data from the GSM module. After WAIT_FOR_DATA_TIMEOUT it gives up.
		@return	- GSMService API request status (GSM_OK, GSM_MODULE_DIDNT_REPLY)
		*/
		GSMRequestStatus waitForGSMmoduleData();

		/*
		Verify if there are information from the GSM module waiting in the SoftwareSerial.
		@return boolean - True: If there was data from the GSM module waiting. False: Otherwise.
		*/
		bool lookForGSMmoduleData();

		/*
		Zero the interal buffer of the library. Normally used before receive data or before using
		the buffer to manage strings.
		*/
		void zeroInternalBuffer();

	};

};

#endif
