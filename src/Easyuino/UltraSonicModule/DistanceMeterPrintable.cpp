#include "../../DistanceMeterPrintable.h"

namespace Easyuino {

	DistanceMeterPrintable::DistanceMeterPrintable(uint8_t triggerPin, uint8_t echoPin)
		: DistanceMeter(triggerPin, echoPin) {
		/* Do Nothing */
	}

	DistanceMeterPrintable::~DistanceMeterPrintable() { /* Do Nothing */}

	char* DistanceMeterPrintable::toString() const {
		char* res = (char*)Utilities::EasyMalloc(sizeof(char) * 25);		// TODO Deharcode this malloc
		snprintf(res, 25, "Distance:%.3f", _distance);
		return res;
	}

};