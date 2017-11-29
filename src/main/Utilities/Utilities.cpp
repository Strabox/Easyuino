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
#include "../../Utilities.h"

#define EXTRA_SAFE_BYTES_MALLOC 1

namespace Easyuino {

	void* Utilities::EasyMalloc(IN unsigned int sizeInBytes) {
		void* resPtr = NULL;
		resPtr = (void*)malloc(sizeInBytes + EXTRA_SAFE_BYTES_MALLOC);
		if (resPtr == NULL) {
			return NULL;
		}
		else {
			memset(resPtr, 0, sizeInBytes + EXTRA_SAFE_BYTES_MALLOC);
			return resPtr;
		}
	}

	void Utilities::ZeroBuffer(IN void *buffer,IN size_t bufferSize) {
		memset(buffer, 0, bufferSize);
	}

	void Utilities::OverrideLastStringChar(IN char* string) {
		int stringLength = strlen(string);
		if (stringLength >= 1) {
			*(string + (sizeof(char) * (stringLength - 1))) = '\0';
		}
	}

	void Utilities::OverrideLastTwoChar(IN char* string) {
		int stringLength = strlen(string);
		if (stringLength >= 1) {
			*(string + (sizeof(char) * (stringLength - 1))) = '\0';
		}
		if (stringLength >= 2) {
			*(string + (sizeof(char) * (stringLength - 2))) = '\0';
		}
	}

	void Utilities::ObtainI2CDeviceAddress(INOUT int* listOfAddresses, IN uint8_t sizeOfList) {
		/*
		Wire.begin();
		byte error, address;
		int nDevices;

		nDevices = 0;
		for (address = 1; address < 127; address++) {
			// The i2c_scanner uses the return value of
			// the Write.endTransmisstion to see if
			// a device did acknowledge to the address.
			Wire.beginTransmission(address);
			error = Wire.endTransmission();

			if (error == 0)
			{
				Serial.print("I2C device found at address 0x");
				if (address<16)
					Serial.print("0");
				Serial.print(address, HEX);
				Serial.println("  !");

				nDevices++;
			}
			else if (error == 4)
			{
				Serial.print("Unknown error at address 0x");
				if (address<16)
					Serial.print("0");
				Serial.println(address, HEX);
			}
		}
		if (nDevices == 0) {
			return - 1;
		}
		else
			Serial.println("done\n");
		*/
	}

}