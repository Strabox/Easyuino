/*
RelayExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::Relay; // Necessary in order to use Relay

int arduinoPin = 6;	   // Arduino pin that controls the relay

Relay relay(arduinoPin);  // Create the Relay object that exposes the API to use

void setup() {
  /*
  - Initialize the Relay API.
  - The first parameter is TRUE if we connect something to the Normally Closed (NC) of the relay,
  and FALSE if we connect to the Normally Open (NO).
  - The second parameter is the digital level of the relay when it is in Normally Closed state.
  This is needed because some relays activate when we put HIGH on the pin and others on LOW.
  */
  relay.begin(false, HIGH);  // Equivalent to: relay.begin() which is the common configuration.
}

void loop() {
  /*
  - Makes the device connected to relay to turn on.
  */
  relay.turnOn();

  delay(2000);

  /*
  - Makes the device connected to relay to turn off.
  */
  relay.turnOff();

  delay(2000);

  /*
  - Return true if the device is on and false if it is off.
  */
  bool result = relay.isOn(); 

  delay(2000);
}