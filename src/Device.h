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
Device.h
*/

#ifndef _EASYUINO_DEVICE_h
#define _EASYUINO_DEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif

#include "Utilities.h"

namespace Easyuino {

	/*
	General class that provides the common API and behaviour for the majority of devices/sensors for Arduino
	*/
	class Device {

	protected:
		/* Used to know if the device is initialized and ready to receive requests */
		bool _isInitialized;

	public:
		/* Constructor called by every sub-classes */
		Device();

		/* Destroy all the resources associated with the device (IF EXISTS) */
		~Device();

	#pragma region Public Pure Virtual Common API Methods

		/* Used to put the device ready to receive requests. Normally this have some default behaviour some
		devices have other API method with same name that receives other arguments to a better customization. 
		@return	- True: If the device was initializer. False: Otherwise.
		*/
		virtual bool begin() = 0;

		/* Used to stop the device. After this the the device will not process API requests. */
		virtual void end() = 0;

	#pragma endregion


	#pragma region Public Common API Methods

		/*
		Verify is the device is initialized and ready to use.
		@return	- True: If device is initialized. False: Otherwise.
		*/
		bool isInitialized() const;

	#pragma endregion

	};

};

#endif
