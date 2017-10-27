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

#include "Device.h"
#include "SMS.h"
#include "Utilities.h"

/* Define API method parameter to be exclusively an input */
#define IN
/* Define API method parameter to be exclusively an output */
#define OUT
/* Define API method parameter that is used as input and output */
#define INOUT

/* It can change from board to board (Use the compatible with your board) */
#define GSM_SIM900_BAUD_RATE 9600

/* IMPORTANT: Size (bytes) of the buffer used internally to receive/send data from/to the GSM board
if you have more memory you can change this (Advisable to change if you will receive Calls or huge SMSs)
*/
#define INTERNAL_BUFFER_SIZE_BYTES 128

/* IMPORTANT: Maximum number of allowed numbers to call and send sms to the board */
#define MAX_NUMBER_OF_ALLOWED_NUMBERS 4

namespace Easyuino {

	/*
	Used to indicate the status of the request to the GSMService API
	*/
	enum GSMRequestStatus {
		/* The request was successful executed */
		GSM_OK = 0,
		/* Happens in many cases where the board answer with things we were not expected due to:
		- Error in our API (e.g: invalid inputs to the GSMService API that we let pass to the board)
		- Defect in the board (not likely) or a general hardware error.
		IMPORTANT: In this case we consider the request failed and we try put all the things in a consistent and previous state.
		*/
		GSM_UNEXPECTED_REPLY = -1,
		/* GSMService API Tried communicate (e.g: send commands) to the board and it didn't answer in reasonable time */
		GSM_BOARD_DIDNT_REPLY = -2,
		/* The GSMService API was not correctly initialized and can't process requests */
		GSM_SERVICE_NOT_INITIALIZED = -3,
		/* When provided an invalid argument to the GSMService API (e.g: negative pin number, negative baud rate, ...) */
		GSM_REQUEST_INVALID_ARGUMENT = -5,
		/* Not possible add more allowed numbers to the GSMService API */
		GSM_MAXIMUM_ALLOWED_NUMBERS_REACHED = -6
	};

	/*
	Interface fot the GSMService API
	*/
	class IGSMService {

	public:

		virtual bool begin(IN unsigned long gsmBoardBaudRate) = 0;

		virtual GSMRequestStatus addAllowedNumber(IN unsigned long phoneNumberToAdd) = 0;

		virtual GSMRequestStatus isAllowed(IN unsigned long phoneNumber, INOUT bool& allowed) = 0;

		virtual GSMRequestStatus removeAllowedNumber(IN unsigned long phoneNumberToRemove) = 0;

		virtual GSMRequestStatus clearAllowedNumbers() = 0;

		virtual GSMRequestStatus beginListenForSMS() = 0;

		virtual GSMRequestStatus availableSMS(INOUT SMS &message, OUT bool &smsRead) = 0;

		virtual GSMRequestStatus sendSMS(IN SMS &sms) = 0;

		virtual GSMRequestStatus deleteAllReadSMS() = 0;

		virtual GSMRequestStatus deleteAllSentAndReadSMS() = 0;

		virtual GSMRequestStatus deleteAllSMS() = 0;

	};

	/*
	Implementation of an GSMService API to interact with the GSM board through a set of well defined methods
	*/
	class GSMService : public IGSMService, public Device {

	private:

		/* Status of calls to private API of the GSMService */
		enum GSMInternalRequestStatus {
			GSM_INTERNAL_OK = 0,
			GSM_INTERNAL_COMMUNICATION_FAILED = -1
		};

		/* Indicate what type and amount of stored SMSs we want to delete (See AT Commands Reference) */
		enum GSMSmsDeleteFlag {
			INDEX_PARAMTER_CHOSEN_ONLY = 0,
			ALL_READ_SMS = 1,
			ALL_SENT_AND_READ_SMS = 2,
			ALL_SMS = 4
		};

		const unsigned long WAIT_FOR_DATA_TIMEOUT = 5000;	// 5 seconds
		const char *AT_OK = "\r\nOK\r\n";
		const char *AT_ERROR = "\r\nERROR\r\n";

		Stream*_outputStream;
		SoftwareSerial* _GSMSerial;

		char _internalBuffer[INTERNAL_BUFFER_SIZE_BYTES];

		unsigned long _allowedNumbers[MAX_NUMBER_OF_ALLOWED_NUMBERS];

		bool _isInitialized;
		bool _readyToReceiveSMS;


	public:

		/*
		Creates a GSMService
		@param txPin		- Pin used to send the serial information to GSM module
		@param rxPin		- Pin used to receive the serial information from GSM module
		@param outputStream	- Stream to output the GSM Module outputs in case of necessary debug
		*/
		GSMService(IN uint8_t txPin, IN uint8_t rxPin, IN Stream &outputStream);

		/*
		Creates a GSMService
		@param txPin		- Pin used to send the serial information to GSM module
		@param rxPin		- Pin used to receive the serial information from GSM module
		*/
		GSMService(IN uint8_t txPin, IN uint8_t rxPin);

		/*
		Deallocates all the internal resources used by the GSMService
		*/
		~GSMService();

		/*  Initialize the communications with the GSM module
		@param gsmBoardBaudRate	- Baud rate of the gsm module used
		@return - True: If begin was success. False: Otherwise
		*/
		bool begin(IN unsigned long gsmBoardBaudRate);

		bool begin();

		/*
		Closes all the communications with the GSM module
		*/
		void end();

		/*
		Add the phone number to the allowed numbers IF it doesn't exist yet.
		@param phoneNumberToAdd - Phone number to add to the allowed numbers
		@return					- GSMService API request status
		*/
		GSMRequestStatus addAllowedNumber(IN unsigned long phoneNumberToAdd);

		/*
		Verify if the phone number is in the list of allowed numbers
		@param phoneNumber	- Number to verify
		@param allowed		- After the method executes: True - If the number is in allowed list or if the list is empty. False - Otherwise.
		@return				- GSMService API request status
		*/
		GSMRequestStatus isAllowed(IN unsigned long phoneNumber, INOUT bool& allowed);

		/*
		Remove the given number from the allowed numbers list (If exists there)
		@param phoneNumberToRemove	- Number to remove from the allowed numbers
		@return						- GSMService API request status
		*/
		GSMRequestStatus removeAllowedNumber(IN unsigned long phoneNumberToRemove);

		/*
		Clear the list for allowed phone numbers ENABLING any number to Call and send SMS to the service and accept it.
		@return	- GSMService API request status
		*/
		GSMRequestStatus clearAllowedNumbers();

		/*
		Start listening for received SMS in the GSM module serial output
		@return	- GSMService API request status
		*/
		GSMRequestStatus beginListenForSMS();

		/*
		Check if there are a new received SMS
		@param message	- Allocated message to be filled by the method
		@param smsRead	- Filled by the API. True if a SMS was available. False otherwise.
		@return			- GSMService API request status
		*/
		GSMRequestStatus availableSMS(INOUT SMS &message, OUT bool &smsRead);

		/*
		Send a SMS through the GSM module
		@param sms	- Filled sms to be sent by the GSM board
		@return		- GSMService API request status
		*/
		GSMRequestStatus sendSMS(IN SMS &sms);

		/*
		Delete all the sms in the GSM module
		@return		- GSMService API request status
		*/
		GSMRequestStatus deleteAllSMS();

		/*
		Detele all the messages that were received and read
		@return		- GSMService API request status
		*/
		GSMRequestStatus deleteAllReadSMS();

		/*
		Delete all the the messages that were received and read plus the sent ones
		@return		- GSMService API request status
		*/
		GSMRequestStatus deleteAllSentAndReadSMS();


	private:

		/*

		*/
		GSMRequestStatus deleteSMS(IN GSMSmsDeleteFlag parameter, IN unsigned int messageIndex = 0);

		/*
		Actively waits for data from the GSM board. After WAIT_FOR_DATA_TIMEOUT it gives up.
		*/
		GSMInternalRequestStatus waitForGSMBoardData();

		/*
		Verify if there are information from the GSM board waiting in the SoftwareSerial
		*/
		bool lookForGSMBoardData();

		/*
		Zero the interal buffer of the library. Normally used before receive data.
		*/
		void zeroInternalBuffer();

	};

};

#endif
