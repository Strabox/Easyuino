/*
GSMServiceExample.ino

WARNING: Running this sketch may cause you to send and SMS from the GSM board expending money.
In this sketch the SMS is only sent if the SIM in GSM board receives one SMS.
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::GSMService;	// Necessary in order to use gSMService API
using Easyuino::SMS;  // Necessary to send an receive SMS

int tx_pin = 7;  // Arduino pin connected to TX pin of the GSM board
int rx_pin = 8;  // Arduino pin connected to RX pin of the GSM board
int power_pin = 9;  // Arduino pin connected to power pin of the GSM board

GSMService gsmService(tx_pin, rx_pin, power_pin);  // Create the GSMService API object

void setup() {
	Serial.begin(9600);
	while (!Serial);  // Necessary for Arduino Leonardo serial monitor use

	/*
	- Turns ON the GSM board.
	- Initialize the GSM Service API with baud rate to talk with the board.
	- You should consult what is the factory baud rate of your gsm board. Some auto detect it so you can choose it.
	*/
	gsmService.begin(9600);

	/*
	- This call will make the GSM service listen for incoming SMSs.
	*/
	gsmService.beginListenForSMS();
}

void loop() {
	bool newSMS = false; // Used to know if there are new SMS available
	bool isOn = false;  // Used to check if the GSM board is turned on
	SMS receivedSMS;  // SMS object used to receive SMS from the API

	/*
	- This API call is used to verify if the gsm board is turned on.
	- The boolean argument is set to true or false inside the method depending on the state of the board.
	*/
	gsmService.isOn(isOn);
	if (isOn) {
		Serial.println(F("GSM Board is ON!"));
	}
	else {
		Serial.println(F("GSM Board is OFF!"));
	}

	delay(1000);

	/*
	- This call will verify if there are new SMS available.
	- The first argument is the sms object that will be filled by the API with the new sms details.
	- The second argument is a boolean that will be true after the call if there are a new sms and false otherwise.
	*/
	gsmService.availableSMS(receivedSMS, newSMS);

	if (newSMS) {
		SMS replySms;

		Serial.println(F("SMS RECEIVED!!!"));
		Serial.print(F("Country Prefix Code: "));
		Serial.println(receivedSMS.getCountryPrefixCode());
		Serial.print(F("From: "));
		Serial.println(receivedSMS.getNumber());
		Serial.print(F("Content: "));
		Serial.println(receivedSMS.getMessage());

		replySms.setCountryPrefixCode(receivedSMS.getCountryPrefixCode());
		replySms.setNumber(receivedSMS.getNumber());
		replySms.setMessage("Arduino is replying :o !!!");

		/*
		- This call will send the reply SMS that we filled (If you have money).
		*/
		gsmService.sendSMS(replySms);

		/*
		- This call deletes all sms (sent and received) that are stored in the GSM Board/SIM.
		- Attention: It is good idea to delete the messages after they are received in order
		to maintain space to store new ones. This is special true if you are using the messages
		to send commands to arduino.
		*/
		gsmService.deleteAllSMS();
	}
	else {
		Serial.println(F("WAITING FOR A SMS!!!"));
	}

	delay(1000);
}