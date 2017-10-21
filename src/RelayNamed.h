/*
RelayNamed.h
*/
#ifndef _EASYUINO_RELAY_NAMED_h
#define _EASYUINO_RELAY_NAMED_h

#include "Device.h"
#include "Printable.h"
#include "Utilities.h"
#include "Relay.h"

#define MAX_NAME_SIZE 15		// Maximum size for a identifier
#define OPEN_STRING "Aberto"
#define CLOSED_STRING "Fechado"

namespace Easyuino {

	/*
	Represents a relay with a label associated to easily identify the device controlled by the relay
	*/
	class RelayNamed : public Relay, public Printable {

	private:
		/* Name of the device that relay activates  */
		char _name[MAX_NAME_SIZE + 1];

	public:
		/*
		Creates a Relay object to interact with the physical relay
		@param arduionPin	- Arduino pin that is connected with the relay (normal in relay is IN pins)
		@param name			- Name (identifier) to the device that the relay activates
		*/
		RelayNamed(uint8_t arduinoPin, const char* deviceName);

		~RelayNamed();

	#pragma region Public Printable API Methods

		char* toString() const;

	#pragma endregion

	};

};

#endif
