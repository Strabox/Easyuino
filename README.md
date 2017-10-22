# Easyuino

Easyuino is a library that offers a modular and set of APIs to several sensors and devices that connects to Arduino (e.g: Relays, RGB Leds, Ultrasonic Modules, Water Detectors, ...). 

The Easyuino library has 5 fundamental goals:
1. Easy to integrate in your favorite IDEs because it works like a common Arduino library
2. Facilitate the use of several common sensors and devices by beginners but provide a useful API for a bit more advanced users
3. Use minimum code and memory footprint (due to controllers flash and sram memory constraints) while maintaining a simple API to extend and develop
4. Put all the sensors API under the same mental/use model to facilitate and speed up the users interest to get new sensors and devices that instigate learning of programming and electronics (Basically support the Arduino foundation ideas)
5. Having fun using Easyuino as much as I have developing it!!!

## Sensors and Devices Support

The development of the library, including fixes and addition of new sensors/devices, will be done depending on:
- My time availability (Now I am doing my Masters Degree Thesis in Computer Science and Engineering that stoles a good slice of my time)
- Interest of people in Easyuino

Important: Nevertheless I will accept suggestions for interesting devices/sensors to develop and if there are a lot of interest I will start prioritize them

Contact Channels:
- Email: easyuino@gmail.com

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

## Getting Started

1. Use GitHub download green button to get the llibrary as a .zip file
2. Using your favorite IDE add the library selecting .zip file
2.1 Using Arduino IDE got to to menu bar choose Sketch > Include Library and select the .zip file downloaded in 1.
3. Have fun!!!
3. [Optional] Look at https://github.com/Strabox/Easyuino/wiki to usage examples and details about the API

## Important: API Usage Examples and Additional Information

**Project's wiki has a set of usage examples of the library API plus more detailed information about it: https://github.com/Strabox/Easyuino/wiki**

## Related and Useful Libraries

https://github.com/Strabox/GSMLibrary I have this Arduino library too that is used to interact with GSM/GPRS boards. It is separated from this one because addresses a much more complex device but follows identical rules of Easyuino.

## Easyuino History

I am Computer Scientist and Engineer (not an Electrotechnical one) that loves programming special in C/C++. 
This library started with a necessity to use several sensors in one personal project and at same time make me practice C/C++ programming and a bit o "low level" programming.
At certain point in the development of the project I decided that isolate all the interfaces with each sensor was a good idea and created this library to help others use the devices easily.

## License 

Copyright (c) 2017 André Pires

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.