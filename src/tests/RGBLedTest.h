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
			rgbLedCatode->setColor(RGBLed::Color::GREEN);
			testEnd();

			testStart("PINK LED");
			rgbLedCatode->setColor(RGBLed::Color::PINK);
			testEnd();

			testStart("WHITE LED");
			rgbLedCatode->setColor(RGBLed::Color::WHITE);
			testEnd();

			testStart("FIREBRICK LED");
			rgbLedCatode->setColor(RGBLed::Color::FIREBRICK);
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
