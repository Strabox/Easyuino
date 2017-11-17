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
SMS.h
*/
#ifndef _EASYUINO_SMS_h
#define _EASYUINO_SMS_h

#include "Utilities.h"

/* Maximum SMS size to allow predictable allocation of resources */
#define MAX_SMS_SIZE 50

namespace Easyuino {

	/*
	Represents a SMS object used to send and receive it from the GSMService API.
	*/
	class SMS {

	private:
		/* Country code used to put in the prefix */
		unsigned int _countryPrefixCode;
		/* Phone number without the country prefix code */
		unsigned long _number;
		/* The content of the SMS */
		char _message[MAX_SMS_SIZE + 1];

	public:
		/*	Create a SMS object used to send/receive SMS from GSMLibrary
		@param number				- Number of sender or receiver
		@param message				- Message content
		@param countryPrefixCode	- Country prefix code of the message. Default value is 351 (Portugal Code)
		*/
		SMS(IN unsigned long number, IN const char* message, IN unsigned int countryPrefixCode = 351);

		/*	Create an empty SMS
		@param number - Country prefix code of the message.Default value is 351 (Portugal Code)
		*/
		SMS(IN unsigned int countryPrefixCode = 351);

		/* Get the country prefix code associated with the SMS
		@return - Number associated with the SMS OR 0 if it was impossible to obtain the prefix code.
		*/
		unsigned int getCountryPrefixCode();

		/* Set the country prefix code associated with the SMS. Valid numbers are in range [0,999].
		@param newCountryPrefixCode - New country prefix code to the SMS
		*/
		void setCountryPrefixCode(IN unsigned int newCountryPrefixCode);

		/* Get the number associated with the SMS
		@return	- Number associated with the SMS
		*/
		unsigned long getNumber();

		/* Set the number of the SMS
		@param number - The new number to be set on the SMS
		*/
		void setNumber(IN unsigned long newNumber);

		/* Get the message associated with the SMS
		@return	- Message associated with the SMS
		*/
		const char* getMessage();

		/* Set the message of the SMS
		@param message - The new message to be set on the SMS
		*/
		void setMessage(IN const char* newMessage);

		/* Resets the message to zeros, number to zero and the country prefix code to 0 (Undefined)*/
		void reset();

	};

};
#endif