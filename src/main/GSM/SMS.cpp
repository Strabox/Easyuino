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
#include "../../SMS.h"

namespace Easyuino {

	SMS::SMS(unsigned long number, const char* message, unsigned int countryPrefixCode)
		: SMS::SMS() {
		setNumber(number);
		setMessage(message);
		setCountryPrefixCode(countryPrefixCode);
	}

	SMS::SMS(unsigned int countryPrefixCode) {
		Utilities::zeroBuffer(_message, MAX_SMS_SIZE + 1);
		setNumber(0);
		setCountryPrefixCode(countryPrefixCode);
	}

	unsigned int SMS::getCountryPrefixCode() {
		return _countryPrefixCode;
	}

	void SMS::setCountryPrefixCode(unsigned int newCountryPrefixCode) {
		_countryPrefixCode = newCountryPrefixCode;
	}

	unsigned long SMS::getNumber() {
		return _number;
	}

	void SMS::setNumber(unsigned long newNumber) {
		_number = newNumber;
	}

	const char* SMS::getMessage() {
		return _message;
	}

	void SMS::setMessage(const char* newMessage) {
		Utilities::zeroBuffer(_message, MAX_SMS_SIZE + 1);
		strncpy(_message, newMessage, MAX_SMS_SIZE);
	}

	void SMS::reset() {
		Utilities::zeroBuffer(_message, MAX_SMS_SIZE + 1);
		setNumber(0);
		setCountryPrefixCode(0);
	}

};