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
Button.h
*/
#ifndef _EASYUINO_TOUCH_BUTTON_h
#define _EASYUINO_TOUCH_BUTTON_h

#include "Utilities.h"
#include "Device.h"

/** Default debounce delay used when verifying the button state (Default 50 ms)*/
#define DEFAULT_DEBOUNCE_DELAY 50 
/** Digital level that is sent by the button when the it is being pressed */
#define BUTTON_PRESSED_DIGITAL_LEVEL HIGH

namespace Easyuino {

	/** Button API offers an interface to interact with common buttons
	@see Devices Supported:	 Touch Button v1.0, Push Buttons
	@see Devices Tested:	 Touch Button v1.0
	*/
	class Button : public Device {

	private:
		/** Arduino pin that is connected to button pin */
		uint8_t _buttonPin;

		/** Last state of the button after a new verification passed the debounce delay */
		uint8_t _lastState;
		/** The current button state (takes in account the button debounce) */
		uint8_t _currentState;
		/** The last time a different verification was done */
		unsigned long _lastReadTimestamp;

	public:
		/** Constructor
		@param buttonPin Arduino pin that is connected to button pin
		*/
		Button(IN uint8_t buttonPin);

		/** Destructor */
		~Button();

		bool begin();

		void end();

		/** Verifies if the button is pressed
		@return isPressed True: If button is currently being pressed. False: Otherwise.
		*/
		bool isPressed();

		/** Return the the time since it is being pressed
		@return pressedTime Time since the button started being pressed (Milliseconds) OR 0 if button is not being pressed
		*/
		unsigned long getPressedTimeMilliseconds();

		/** Return the the time since it is being pressed
		@return pressedTime Time since the button started being pressed (Seconds) OR 0 if button is not being pressed
		*/
		unsigned int getPressedTimeSeconds();

	};

};

#endif
