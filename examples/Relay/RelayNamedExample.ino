/*
RelayNamedExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::RelayNamed;  // Necessary in order to use RelayNamed

int arduinoPin = 6;				// Arduino pin that controls the relay
char* controlledDevice = "Lamp";// The difference for normal relay is that the relay stays with a name identifier name attached	

RelayNamed relayNamed(arduinoPin, controlledDevice);  // Create the RelayNamed object that exposes the API to use

void setup() {
	Serial.begin(9600);  // Used to start the serial connection with the computer. Change the 9600 if needed.
	relayNamed.begin(false, HIGH);	// See RelayExample.ino for the explanation
}

void loop() {
	bool result;

	relayNamed.turnOn(); // Makes the device connected to relay to turn on
	result = relayNamed.isOn();  // result would be TRUE

	delay(2000);

	relayNamed.turnOff();  // Makes the device connected to relay to turn off
	result = relayNamed.isOn();  // result would be FALSE

	delay(2000);

	/*
	- state would be "Lamp:Off" which is useful for print into the serial monitor to debug.
	*/
	char* state = relayNamed.toString();

	/*
	- When you don't need the content of the state string you must
	call this to avoid filling the memory and crashing the program.
	*/
	free(state);

	delay(2000);

	/*
	- This instruction will automatically print the toString() method result to the serial monitor.
	- BEGINNERS should use this code to print instead of the one above because this frees the string automatically.
	- It is equally of doing the following code:
	char* state = relay.toString();
	Serial.print(state);
	free(state);
	*/
	Serial << relayNamed;
	Serial.println();

	delay(2000);

	relayNamed.turnOn();

	delay(2000);

	Serial << relayNamed;
	Serial.println();

	/*
	- This method will turn off the device and after that no more calls to
	the relay will be possible without call the relay.begin(); again.
	*/
	relayNamed.end();
}