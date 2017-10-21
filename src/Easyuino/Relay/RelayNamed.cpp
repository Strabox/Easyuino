#include "../../RelayNamed.h"

namespace Easyuino {

	RelayNamed::RelayNamed(uint8_t arduinoPin, const char * deviceName) : Relay(arduinoPin) {
		memset(_name, NULL, MAX_NAME_SIZE);
		strncpy(_name, deviceName, MAX_NAME_SIZE);
	}

	RelayNamed::~RelayNamed() { /* Do Nothing */ }

	char* RelayNamed::toString() const {
		const char delimiter = ':';
		char* res = NULL;
		unsigned int resSize = 0;
		if (isOpen()) {
			resSize = strlen(_name) + 1 + strlen(OPEN_STRING);
			res = (char*)Utilities::EasyMalloc(sizeof(char) * resSize);
			snprintf(res, resSize, "%s%c%s", _name, delimiter, OPEN_STRING);
		}
		else {
			resSize = strlen(_name) + 1 + strlen(CLOSED_STRING);
			res = (char*)Utilities::EasyMalloc(sizeof(char) * resSize);
			snprintf(res, resSize, "%s%c%s", _name, delimiter, CLOSED_STRING);
		}
		return res;
	}

};