/*
RGBLedTest.h
*/
#ifndef _EASYUINO_RGB_LET_TEST_h
#define _EASYUINO_RGB_LED_TEST_h

#include "Easyuino.h"
#include "ManualTest.h"

using Easyuino::RGBLed;

class RGBLedTest : public ManualTest {

	private:
		RGBLed* rgbLedCatode;

	public:
		RGBLedTest(Stream &debugStream, uint8_t redPin, uint8_t greenPin, uint8_t bluePin) : 
			ManualTest(debugStream) {
			rgbLedCatode = new RGBLed(redPin, greenPin, bluePin, RGBLed::COMMON_CATODE);
		}

	protected:
		void testsSetup() {
			rgbLedCatode->begin();
		}

		void tests() {
			testStart("RED LED");
			rgbLedCatode->setColor(255, 0, 0);
			testEnd();

			testStart("GREEN LED");
			rgbLedCatode->setColor(0, 255, 0);
			testEnd();

			testStart("BLUE LED");
			rgbLedCatode->setColor(0, 0, 255);
			testEnd();

			testStart("LED OFF");
			rgbLedCatode->turnOff();
			testEnd();

			testStart("LED ORANGE");
			rgbLedCatode->setColor("#ff6600");
			testEnd();

			testStart("GREEN LED");
			rgbLedCatode->setColor(RGBLed::COLOR::GREEN);
			testEnd();

			testStart("PINK LED");
			rgbLedCatode->setColor(RGBLed::COLOR::PINK);
			testEnd();

			testStart("WHITE LED");
			rgbLedCatode->setColor(RGBLed::COLOR::WHITE);
			testEnd();

			testStart("FIREBRICK LED");
			rgbLedCatode->setColor(RGBLed::COLOR::FIREBRICK);
			testEnd();

			testStart("END RGB LED => LED OFF");
			rgbLedCatode->end();
			testEnd();

			testStart("LED MAINTAIN OFF");
			rgbLedCatode->setColor(0,0,255);
			testEnd();
		}

		void afterTestSuite() {
			rgbLedCatode->end();
			delete rgbLedCatode;
			rgbLedCatode = NULL;
		}

};

#endif
