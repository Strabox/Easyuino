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

	/** Relay offers a simple API to interact with relay devices. 
	@see Devices Supported:	SRD-05VDC-SL-C, Probably any relay because they are very simple devices
	@see Devices Tested:	SRD-05VDC-SL-C
	*/
	class Relay : public Device {

	private:
		/** Arduino pin that controls the relay */
		uint8_t _arduinoPin;
		/** Used to know if the device powered by the relay is ON or OFF */
		bool _isOn;

	public:
		/** Constructor
		@param arduinoPin	Arduino pin that is connected with the relay (normaly called IN pins in the relay boards)
		*/
		Relay(IN uint8_t arduinoPin);

		/** Destructor */
		~Relay();

		bool begin();

		/** Used to initialize the relay API depending on how the relay will be connected
		@param isNormallyClosed			Define what are the state that relay is powering the device (lamp, engine, etc) Normally Closed or Normally Open
		@param normallyClosedPinLevel	Digital level of the normally closed relay state (some relays activate on HIGH other on LOW)
		*/
		bool begin(IN bool isNormallyClosed, IN uint8_t normallyClosedPinLevel);

		void end();

		/** Turns on the device that is connected to the relay (depends on how the begin(bool,uint8_t) was called) */
		void turnOn();

		/** Turns off the device that is connected to the relay (depends on how the begin(bool,uint8_t) was called) */
		void turnOff();

		/** @return	isON True: If it is in open state. False: Otherwise. */
		bool isOn() const;

	};

};

#endif
