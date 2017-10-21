/*
RelayNamedExample.cpp
*/

#include <Easyuino.h>	// Include the library in order to the compiler know you want Easyuino library

using Easyuino::RelayNamed;	// Necessary in order to use RelayNamed

int arduinoPin = 6;				// Arduino pin that controls the relay
char* controlledDevice = "Lamp";// The difference for normal relay is the name given to it to debug for example	

RelayNamed relayNamed(arduinoPin, controlledDevice);	// Create the RelayNamed object that exposes the API to use

void setup() {
	relayNamed.begin();	// Called in setup method to initialize it in order to accept requests
}

void loop() {


}