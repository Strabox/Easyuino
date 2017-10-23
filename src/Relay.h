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

#include "Device.h"

namespace Easyuino {

	/* Represents a single relay and provides a simple API to interact with the physical it. */
	class Relay : public Device {

	private:
		/* Arduino pin that controls the relay */
		uint8_t _arduinoPin;
		/* Used to know the logical position of the relay */
		bool _isOpen;

	public:
		/*
		Creates a Relay object to interact with the physical one
		@param arduionPin	- Arduino pin that is connected with the relay (normaly called IN pins)
		*/
		Relay(uint8_t arduinoPin);

		/*
		Used to free all the resources associated with the object Relay
		*/
		~Relay();

		#pragma region Public Device API Methods

		void begin();

		void end();

		#pragma endregion

		#pragma region Public Relay API Methods 

		/*
		Used to initialize the relay API with a custom closed pin level depending on the wanted semantic.
		@param closedStatePinLevel	- Define the start relay pin level of the Closed State
		*/
		void begin(uint8_t closedStatePinLevel);

		/*
		If the relay is in closed state opens it
		*/
		void open();

		/*
		If the relay is in open state closes it
		*/
		void close();

		/*
		@return	- True: If it is in open state. False: Otherwise.
		*/
		bool isOpen() const;

		#pragma endregion

	};

};

#endif
