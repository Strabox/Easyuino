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
Relay.h
*/
#ifndef _EASYUINO_RELAY_h
#define _EASYUINO_RELAY_h

#include "Utilities.h"
#include "Device.h"

namespace Easyuino {

	/* 
	Represents a single relay and provides a simple API to interact with it. 
	@Physical Devices Supported: 
		- SRD-05VDC-SL-C, Probably any relay because they are very simple devices
	@Physical Devices Tested: 
		- SRD-05VDC-SL-C
	*/
	class Relay : public Device {

	private:
		/* Arduino pin that controls the relay */
		uint8_t _arduinoPin;
		/* Used to know if the device powered by the relay is ON or OFF */
		bool _isOn;

	public:
		/*
		Creates a Relay object to interact with the physical one
		@param arduionPin	- Arduino pin that is connected with the relay (normaly called IN pins)
		*/
		Relay(IN uint8_t arduinoPin);

		/*
		Used to free all the resources associated with the Relay object
		*/
		~Relay();

		bool begin();

		/*
		Used to initialize the relay API depending on where the relay will be connected
		@param isNormallyClosed			- Define what are the state that relay is powering the device (lamp, engine, etc)
		@param normallyClosedPinLevel	- Digital level of the normally closed relay state (some relays activate on HIGH other on LOW)
		*/
		bool begin(IN bool isNormallyClosed, IN uint8_t normallyClosedPinLevel);

		void end();

		/*
		If the relay is in closed state opens it
		*/
		void turnOn();

		/*
		If the relay is in open state closes it
		*/
		void turnOff();

		/*
		@return	- True: If it is in open state. False: Otherwise.
		*/
		bool isOn() const;

	};

};

#endif
