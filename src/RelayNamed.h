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
RelayNamed.h
*/
#ifndef _EASYUINO_RELAY_NAMED_h
#define _EASYUINO_RELAY_NAMED_h

#include "Device.h"
#include "Printable.h"
#include "Utilities.h"
#include "Relay.h"

#define MAX_NAME_SIZE 15		// Maximum size for a identifier
#define RELAY_ON_STRING "On"
#define RELAY_OFF_STRING "Off"

namespace Easyuino {

	/*
	Represents a relay with a label associated to easily identify the device controlled by the relay
	@Physical Devices Supported:
	- SRD-05VDC-SL-C, Probably any relay because they are very simple devices
	@Physical Devices Tested:
	- SRD-05VDC-SL-C
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

		char* toString() const;

	};

};

#endif
