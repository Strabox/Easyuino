/*
GSMServiceSecureExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::GSMServiceSecure;	// Necessary in order to use GSMServiceSecure API
using Easyuino::SMS;  // Necessary to send an receive SMS

int tx_pin = 7;  // Arduino pin connected to TX pin of the GSM board
int rx_pin = 8;  // Arduino pin connected to RX pin of the GSM board
int power_pin = 9;  // Arduino pin connected to power pin of the GSM board
unsigned long allowedPhoneNumber = 976323122;  // Phone number that are allowed to send SMS to the GSMService

GSMServiceSecure gsmServiceSecure(tx_pin, rx_pin, power_pin);

void setup() {
	bool isAllowed = false;

	Serial.begin(9600);
	while (!Serial);  // Necessary for Arduino Leonardo serial monitor use

	/*
	- Turns ON the GSM board.
	- Initialize the GSM Service API with baud rate to talk with the board.
	- You should consult what is the factory baud rate of your gsm board. Some auto detect it so you can choose it.
	*/
	gsmServiceSecure.begin(9600);

	/*
	- This will add the phone number to a list of phone numbers that can send SMS to the GSMServiceSecure.
	- GSMServiceSecure API will never make available to the application SMS's from other numbers that are not in the list.
	- You can add up to four phone numbers.
	- IF you don't add any number the default behaviour is accept SMSs from all numbers as in GSMService normal API.
	- You can use API call removeAllowedNumber(phoneNumber) to remove it from the list.
	*/
	gsmServiceSecure.addAllowedNumber(allowedPhoneNumber);

	/*
	- API call used to verify if a given numver is in the allowed list.
	*/
	gsmServiceSecure.isAllowed(allowedPhoneNumber, isAllowed);

	if (isAllowed) {
		Serial.println(F("Number Allowed"));
	}

	/*
	- This call will make the GSM service listen for incoming SMSs.
	*/
	gsmServiceSecure.beginListenForSMS();
}


void loop() {
	SMS receivedSMS;  // SMS object used to receive SMS from the API
	bool newSMS = false; // Used to know if there are new SMSs available

	gsmServiceSecure.availableSMS(receivedSMS, newSMS);

	if (newSMS) {
		Serial.println(F("SMS FROM AN ALLOWED NUMBER RECEIVED!!!"));
		Serial.print(F("Country Prefix Code: "));
		Serial.println(receivedSMS.getCountryPrefixCode());
		Serial.print(F("From: "));
		Serial.println(receivedSMS.getNumber());
		Serial.print(F("Content: "));
		Serial.println(receivedSMS.getMessage());
	}

	delay(1000);
}