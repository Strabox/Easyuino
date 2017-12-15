/*
ButtonExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::Button;  // Necessary in order to use Button API

int pressedPin = 7;  // Arduino pin that connects to Button (used to know if button is pressed or not)

Button button(pressedPin);  // Create the Button API object

void setup() {
	Serial.begin(9600);
	while (!Serial);  // Necessary for Arduino Leonardo serial monitor use

	button.begin();  // Initialize the Button API
}

void loop() {
	unsigned long timePressed = 0;

	/*
	- API call used to verify if the button is being pressed.
	*/
	if (button.isPressed()) {
		Serial.println(F("PRESSED!!"));

		/*
		- API call used to obtain how many milliseconds have past since the button is being pressed.
		*/
		timePressed = button.getPressedTimeMilliseconds();
		Serial.println(timePressed);
	}
	else {
		Serial.println(F("IDLE"));
	}

}