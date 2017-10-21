/*
Printable.h
*/

#ifndef _EASYUINO_PRINTABLE_h
#define _EASYUINO_PRINTABLE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif

namespace Easyuino {

	/*
	Provides some devices implementations with an interface to write themeselves to a stream.
	Useful for debug the current state of the device.
	*/
	class Printable {

	#pragma region Public Virtual Common API Methods

	public:
		/* Used to return a string representation of the Device state.
		IMPORTANT: It is mandatory to free the returned pointer in order to have no memory leaks. */
		virtual char* toString() const = 0;

	#pragma endregion

		/* Write the Device state string representation to a given stream (e.g: Used to Debug) */
		friend Stream& operator<<(Stream & stream, const Printable& printable);

	};

};

#endif
