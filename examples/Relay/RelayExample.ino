/*
RelayExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::Relay; // Necessary in order to use Relay

int arduinoPin = 6;  // Arduino pin that controls the relay

Relay relay(arduinoPin);  // Create the Relay object that exposes the API to use

void setup() {
  /*
  - Initialize the Relay API.
  - The first parameter is TRUE if we connect something to the Normally Closed (NC) of the relay,
  and FALSE if we connect to the Normally Open (NO).
  - The second parameter is the level of the relay when it is in Normally Closed state.
  This is needed because some relays activate when we put HIGH on the pin and others on LOW.
  - relay.begin(); is equal to relay.begin(false, HIGH); which is the common configuration.
  */
  relay.begin(false, HIGH);
}

void loop() {
  /*
  Makes the device connected to relay to turn on
  */
  relay.turnOn();

  delay(2000);

  /*
  Makes the device connected to relay to turn off
  */
  relay.turnOff();

  delay(2000);

  /*
  Return TRUE if the device is on and FALSE if it is off
  */
  bool result = relay.isOn(); 

  /*
  - This method will turn off the relay and after that no more calls to
  the relay will work without call the relay.begin(); again.
  */
  relay.end();
}