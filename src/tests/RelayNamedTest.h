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
RelayNamedTest.h
*/
#ifndef _EASYUINO_RELAY_NAMED_TEST_h
#define _EASYUINO_RELAY_NAMED_TEST_h

#include "Easyuino.h"
#include "ManualTest.h"

using Easyuino::RelayNamed;

class RelayNamedTest : public ManualTest {

	private:
		RelayNamed* relay;

	public:
		RelayNamedTest(Stream &debugStream, uint8_t arduinoPin, const char* relayName) : ManualTest(debugStream) {
			relay = new RelayNamed(arduinoPin, relayName);
		}

	protected:
		void testsSetup() {
			relay->begin(false, HIGH);
		}

		void tests() {
			testStart("1.TO STRING");
			_debugStream->print(relay->toString());
			_debugStream->println("|");				// To mark the end of string
			testEnd();

			testStart("2.<<");
			*_debugStream << *relay;
			_debugStream->println("|");				// To mark the end of string
			testEnd();

			testStart("3.ON");
			relay->turnOn();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("4.NOTHING");
			relay->turnOn();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("5.OFF");
			relay->turnOff();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("6.NOTHING");
			relay->turnOff();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("7.ON");
			relay->turnOn();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("8.OFF");
			relay->end();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("9.NOTHING");
			relay->turnOff();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("10.NOTHING");
			relay->begin(false, HIGH);
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("11.ON");
			relay->turnOn();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("12.OFF");
			relay->turnOff();
			_debugStream->println(relay->isOn());
			testEnd();
		}

		void afterTestSuite() {
			relay->end();
			delete relay;
			relay = NULL;
	}

};

#endif
