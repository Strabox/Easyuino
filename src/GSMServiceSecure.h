/*
MIT License

Copyright (c) 2017 Andr� Pires

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
GSMServiceSecure.h
*/
#ifndef _EASYUINO_GSM_SERVICE_SECURE_h
#define _EASYUINO_GSM_SERVICE_SECURE_h

#include "Utilities.h"
#include "GSMService.h"
#include "SMS.h"

/* IMPORTANT: Maximum number of allowed numbers to do CALLS and send SMS to the module */
#define MAX_NUMBER_OF_ALLOWED_NUMBERS 3

namespace Easyuino {

	/*
	GSMServiceSecure expands the GSMService API allowing user to add phone numbers
	to filter calls and SMSs.
	@Physical Devices Supported:
	- SIM90x Series Chipset, SIM80x Chipset
	@Physical Devices Tested:
	- SIM900 Chipset
	*/
	class GSMServiceSecure : public GSMService {

	private:
		/* The numbers that are allowed to send SMS to the module */
		unsigned long _allowedNumbers[MAX_NUMBER_OF_ALLOWED_NUMBERS];

	public:
		/*
		Creates a GSMServiceSecure API object.
		@param txPin		- Pin used to send the serial information to GSM module
		@param rxPin		- Pin used to receive the serial information from GSM module
		@param powerPin		- Pin used to turn on and off the GSM module
		@param outputStream	- Stream to output the GSM Module outputs in case of necessary debug
		*/
		GSMServiceSecure(IN uint8_t txPin, IN uint8_t rxPin, IN uint8_t powerPin, IN Stream &outputStream);

		/*
		Creates a GSMServiceSecure API object.
		@param txPin	- Pin used to send the serial information to GSM module
		@param rxPin	- Pin used to receive the serial information from GSM module
		@param powerPin	- Pin used to turn on and off the GSM module
		*/
		GSMServiceSecure(IN uint8_t txPin, IN uint8_t rxPin, IN uint8_t powerPin);

		/* Deallocates all the internal resources used by the GSMService */
		~GSMServiceSecure();

#pragma region Controller Numbers Management

		/*
		Add the phone number to the allowed numbers IF it doesn't exist yet.
		@param phoneNumberToAdd - Phone number to add to the allowed numbers
		@return					- GSMService API request status (NOT_INITIALIZED, GSM_REQUEST_INVALID_ARGUMENT, GSM_OK, GSM_MAXIMUM_ALLOWED_NUMBERS_REACHED)
		*/
		GSMRequestStatus addAllowedNumber(IN unsigned long phoneNumberToAdd);

		/*
		Verify if the phone number is in the list of allowed numbers
		@param phoneNumber	- Number to verify
		@param allowed		- After the method executes. True: If the number is in allowed list or if the list is empty. False: Otherwise.
		@return				- GSMService API request status (NOT_INITIALIZED, GSM_REQUEST_INVALID_ARGUMENT, GSM_OK)
		*/
		GSMRequestStatus isAllowed(IN unsigned long phoneNumber, OUT bool& allowed);

		/*
		Remove the given number from the allowed numbers list (If exists there)
		@param phoneNumberToRemove	- Number to remove from the allowed numbers
		@return						- GSMService API request status
		*/
		GSMRequestStatus removeAllowedNumber(IN unsigned long phoneNumberToRemove);

		/*
		Clear the list for allowed phone numbers ENABLING any number to Call and send SMS to the service and accept it.
		@return	- GSMService API request status (NOT_INITIALIZED, GSM_OK)
		*/
		GSMRequestStatus clearAllowedNumbers();

#pragma endregion 

#pragma region SMS Management

		virtual GSMRequestStatus availableSMS(INOUT SMS &message, OUT bool &smsRead);

#pragma endregion
	
	};

};

#endif
