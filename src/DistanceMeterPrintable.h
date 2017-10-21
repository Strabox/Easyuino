/*
DistanceMeterPrintable.h
*/
#ifndef _EASYUINO_DISTANCE_METER_PRINTABLE_h
#define _EASYUINO_DISTANCE_METER_PRINTABLE_h

#include "Printable.h"
#include "DistanceMeter.h"
#include "Utilities.h"

namespace Easyuino {

	/*
	It offers the same API as DistanceMetter plus some functions to print the internal state into a stream for example.
	Useful for debugging purposes.
	*/
	class DistanceMeterPrintable : public DistanceMeter, public Printable {

	public:
		DistanceMeterPrintable(uint8_t triggerPin, uint8_t echoPin);

		~DistanceMeterPrintable();

	#pragma region Public Printable API Methods

		char* toString() const;

	#pragma endregion

	};

};


#endif
