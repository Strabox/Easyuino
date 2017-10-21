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
