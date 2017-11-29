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
DistanceMeterPrintable.h
*/
#ifndef _EASYUINO_DISTANCE_METER_PRINTABLE_h
#define _EASYUINO_DISTANCE_METER_PRINTABLE_h

#include "Utilities.h"
#include "Printable.h"
#include "DistanceMeter.h"

namespace Easyuino {

	/** It offers the same API as DistanceMeter plus some methods to print the internal state into a stream for example.
	Useful for debugging purposes.
	@see Devices Supported:	 HC-SR03, HC-SR04, HC-SR05
	@see Devices Tested:	 HC-SR04
	*/
	class DistanceMeterPrintable : public DistanceMeter, public Printable {

	public:
		/** Constructor similar to the DistanceMeter one.
		@param triggerPin	Arduino pin connected to the trigger pin of the Ultrasonic Module
		@param echoPin		Arduino pin connected to the echo pin of the Ultrasonic Module
		*/
		DistanceMeterPrintable(IN uint8_t triggerPin, IN uint8_t echoPin);

		/** Destructor */
		~DistanceMeterPrintable();

	#pragma region Public Printable API Methods

		char* toString() const;

	#pragma endregion

	};

};


#endif
