/*
SevenSegmentsExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::SevenSegments; // Necessary in order to use SevenSegments API

int clkPin = 6;  // Arduino pin connected to CLK pin of the display
int dataPin = 7; // Arduino pin connected to DATA pin of the display

SevenSegments display(clkPin, dataPin);  // Create SevenSegments API object

void setup() {
	display.begin();  // Initializes the SevenSegments API
}

void loop() {

	delay(3000);

	/*
	- Sets the brigthness of the display.
	- It accepts values from 0 to 7, in increasing order of brightness.
	*/
	display.setBrightness(1);

	delay(2000);

	/*
	- Prints the given number into the display.
	*/
	display.print(4379);

	delay(2000);

	/*
	- Prints the given number into the display.
	*/
	display.print(-367);

	delay(2000);

	/*
	- Prints the digit (0-9) given in first argument, to the position (0-3) given in the second.
	- The positions start with left most seven segment display.
	*/
	display.print(7, 0);

	delay(2000);

	while (true) {
		/*
		- Prints the given string into the display.
		*/
		display.print("HeLo");

		delay(500);

		display.print("");

		delay(500);
	}

}