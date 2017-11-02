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
#include "../../RelayNamed.h"

namespace Easyuino {

	RelayNamed::RelayNamed(IN uint8_t arduinoPin, IN const char * deviceName) : Relay(arduinoPin) {
		memset(_name, 0, MAX_NAME_SIZE);
		strncpy(_name, deviceName, MAX_NAME_SIZE);
	}

	RelayNamed::~RelayNamed() { /* Do Nothing */ }

	char* RelayNamed::toString() const {
		const char delimiter = ':';
		char* res = NULL;
		unsigned int resSize = 0;
		if (isOn()) {
			resSize = strlen(_name) + 1 + strlen(RELAY_ON_STRING) + 1;
			res = (char*)Utilities::EasyMalloc(sizeof(char) * resSize);
			snprintf(res, resSize, "%s%c%s", _name, delimiter, RELAY_ON_STRING);
		}
		else {
			resSize = strlen(_name) + 1 + strlen(RELAY_OFF_STRING) + 1;
			res = (char*)Utilities::EasyMalloc(sizeof(char) * resSize);
			snprintf(res, resSize, "%s%c%s", _name, delimiter, RELAY_OFF_STRING);
		}
		return res;
	}

};