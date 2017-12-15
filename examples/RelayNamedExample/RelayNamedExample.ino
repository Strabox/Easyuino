/*
RelayNamedExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::RelayNamed;  // Necessary in order to use RelayNamed

int arduinoPin = 6;  // Arduino pin that controls the relay
const char* controlledDevice = "Lamp"; // The difference for normal relay is that the relay stays with a name identifier name attached	

RelayNamed relayNamed(arduinoPin, controlledDevice);  // Create the RelayNamed object that exposes the API to use

void setup() {
  Serial.begin(9600);  // Used to start the serial connection with the computer. Change the 9600 if needed.
  while (!Serial);  // Necessary for Arduino Leonardo serial monitor use

  relayNamed.begin(false, HIGH);  // See RelayExample.ino for the explanation
}

void loop() {
  bool result;

  relayNamed.turnOn(); // Makes the device connected to relay to turn on
  result = relayNamed.isOn();  // result would be true

  delay(2000);

  relayNamed.turnOff();  // Makes the device connected to relay to turn off
  result = relayNamed.isOn();  // result would be false

  delay(2000);

  /*
  - State would be "Lamp:Off" which is useful for print into the serial monitor to debug.
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
  Serial.println();  // It is here only to print a new line

  delay(2000);

  relayNamed.turnOn();

  delay(2000);

  Serial << relayNamed;
  Serial.println();

  delay(2000);
}