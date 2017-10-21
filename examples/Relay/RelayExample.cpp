/*
RelayExample.cpp
*/

#include <Easyuino.h>	// Include the library in order to the compiler know you want Easyuino library

using Easyuino::Relay;	// Necessary in order to use Relay

int arduinoPin = 6;		// Arduino pin that controls the relay

Relay relay(arduinoPin);	// Create the Relay object that exposes the API to use

void setup() {
	relay.begin();	// Called in setup method to initialize the Relay in order to accept requests
}

void loop() {


}