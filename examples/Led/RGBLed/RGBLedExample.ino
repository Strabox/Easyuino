/*
RGBLedExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::RGBLed;	// Necessary in order to use RGBLed
using Easyuino::Color;  // Necessary for some method calls

int red_pin = 9;  // Arduino pin connected to led red pin
int green_pin = 10;  // Arduino pin connected to led green pin
int blue_pin = 11;  // Arduino pin connected to led blue pin

RGBLed led(red_pin, green_pin, blue_pin);  // Create the RGBLed object that exposes the API to use

void setup() {
  led.begin();  // Called in setup method to initialize the RGBLed in order to accept requests
}

void loop() {
  /*
  - This method call sets the color to YELLOW. There are several ones
  you can chose normally as seen in the list below.
  - List of Colors Available: RED, GREEN, BLUE, YELLOW, WHITE, ORANGE,
  PINK, SALMON, VIOLET, AQUA, BROWN, FIREBRICK, DARKGREY, OLIVE, SKYBLUE
  */
  led.setColor(Color::YELLOW);

  delay(2000);

  /*
  - This method call set the led color to RED.
  - First parameter controls the amount of red (0-255).
  - First parameter controls the amount of green (0-255).
  - First parameter controls the amount of blue (0-255).
  - The color of the led will be the overlap of the amount of 3 colors. See:
  https://en.wikipedia.org/wiki/Additive_color
  - You can use this link to pick up RGB colors:
  https://www.w3schools.com/colors/colors_picker.asp
  */
  led.setColor(255, 0, 0);

  delay(2000);

  /* This method call set the led to WHITE */
  led.setColor(255, 255, 255);

  delay(2000);

  /* This method call will TURN OFF the led */
  led.turnOff();

  delay(2000);

  /*
  - This method will set the color to BLUE. See Hexadecimal color code on how to use it.
  - You can use this link to pick up Heaxadecimal codes https://www.w3schools.com/colors/colors_picker.asp
  */
  led.setColor("#0000ff");

  delay(2000);

  /*
  - This method will turn off the led. After this call you can't set
  the color of the led anymore while led.begin(); is not called again.
  */
  led.end();
}