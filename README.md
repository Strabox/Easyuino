# Easyuino

Easyuino is a library that offers a modular and set of APIs to several sensors and devices that connects to Arduino (e.g: Relays, RGB Leds, Ultrasonic Modules, Water Detectors, ...). 

The Easyuino library has 4 fundamental goals:
1. Facilitate the use of several common sensors and devices by beginners but provide a useful API for other users
2. Use minimum code and memory footprint (due to controllers flash and sram memory constraints) while maintaining a simple API to extend and develop
3. Put all the sensors API under the same mental/use model to facilitate and speed up the users interest to get new sensors and devices that instigate learning of programming and electronics (Basically support the Arduino foundation ideas)
4. Having fun using Easyuino as much as I have developing it!!!

## Sensors and Devices Support

The development of the library, including fixes and addition of new sensors/devices, will be done depending on:
- My time availability (Now I am doing my Masters Degree Thesis in Computer Science and Engineering that stoles a good slice of my time)
- Interest of people in my Easyuino work

Important: Nevertheless I will accept suggestions for interesting devices/sensors to develop and if there are a lot of interest I will start prioritize them
Contact Channels: TODO

### Already Implemented, Documented and Tested = Ready to Use

- RGB Led

### Currently Developing

- Ultrasonic Module (as a Distance Meter)
- Relays

### Develop in a Near Future

- Water Detector
- Infra Red Receiver
- Displays: OLED lcd and Seven Segments

### Develop in a Long Term Future

- Temperature/Humidity sensor
- Photoresistors/Light sensor
- Knock sensor
- Sound sensor
- Optical Fingerprint sensor
- Methane/Gas sensor
- ...

### Important: API Usage Examples and Additional Information

**Project's wiki has a set of usage examples of the library API plus more detailed information https://github.com/Strabox/Easyuino/wiki**

## Getting Started

1. Copy the folder *Easyuino/Easyuino* of the repository to the Arduino Libraries folder (usually the destination folder copy to is something like this "C:\Program Files (x86)\Arduino\libraries" in Windows) 
2. Put *#include <Easyuino.h>* in your sketch file.
3. In the top of the file where you want some of library code put, below the include of step 2, *using Easyuino::Relay* to use for example the relay API.
4. Now you can use the Relay class in your file that offers the API to interact with a relay.

## Project Structure

The library was made using VisualMicro http://www.visualmicro.com/ plugin for Microsoft Visual Studio 2017 due to the great tool support of VS.

The solution has 2 projects:
- Easyuino: This one contains the library code and some example files also found in project wiki https://github.com/Strabox/Easyuino/wiki
- EasyuinoManualTests: This project is used only to maintain some test sketches to run the code in real devices.

## Related and Useful Libraries

https://github.com/Strabox/GSMLibrary I have this Arduino library too that is used to interact with GSM/GPRS boards. It is separated from this one because addresses a much more complex device but follows identical rules of Easyuino.

## Easyuino History

I am Computer Scientist and Engineer (not an Electrotechnical one) that loves programming special in C/C++. 
This library started with a necessity to use several sensors in one personal project and at same time make me practice C/C++ programming and a bit o "low level" programming.
At certain point in the development of the project I decided that isolate all the interfaces with each sensor was a good idea and created this library to help others use the devices easily.
