/*
RelayTest.h
*/
#ifndef _EASYUINO_RELAY_TEST_h
#define _EASYUINO_RELAY_TEST_h

#include "Easyuino.h"
#include "ManualTest.h"

using Easyuino::Relay;

class RelayTest : public ManualTest {

	private:
		Relay* relay;

	public:
		RelayTest(Stream &debugStream, uint8_t arduinoPin) : ManualTest(debugStream) {
			relay = new Relay(arduinoPin);
		}

	protected:
		void testsSetup() {
			relay->begin();
		}

		void tests() {

		}

		void afterTestSuite() {
			relay->end();
			delete relay;
			relay = NULL;
		}

};

#endif
