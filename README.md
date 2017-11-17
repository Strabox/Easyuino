# Easyuino [![Build Status](https://travis-ci.org/Strabox/Easyuino.svg?branch=master)](https://travis-ci.org/Strabox/Easyuino)

## Table of Contents

- [What is Easyuino?](https://github.com/Strabox/Easyuino#what-is-easyuino?)
- [List of Sensors and Devices](https://github.com/Strabox/Easyuino#list-of-sensors-and-devices)
	* [Currently Supported](https://github.com/Strabox/Easyuino#currently-supported)
	* [Under Development](https://github.com/Strabox/Easyuino#under-development)
	* [Future Development](https://github.com/Strabox/Easyuino#future-development)
- [Installation](https://github.com/Strabox/Easyuino#installation)
- [Getting Started](https://github.com/Strabox/Easyuino#getting-started)
- [Library Maintenance](https://github.com/Strabox/Easyuino#library-maintenance)
- [Important Features (Advanced)](https://github.com/Strabox/Easyuino#important-features-(advanced))
	* [Static Memory Allocation](https://github.com/Strabox/Easyuino#static-memory-allocation)
	* [Modular API](https://github.com/Strabox/Easyuino#modular-api)
- [API Version System](https://github.com/Strabox/Easyuino#api-version-system)
- [Easyuino History Briefly](https://github.com/Strabox/Easyuino#easyuino-history-briefly)
- [License](https://github.com/Strabox/Easyuino#license)

## What is Easyuino ?

Easyuino is an Arduino library that offers a modular and set of APIs to several common sensors and devices (e.g: Relays, RGB Leds, Ultrasonic Modules, ...) to be easily used by beginners

The Easyuino library has 4 fundamental goals:
1. Easy to integrate in projects because it works like a common Arduino library
2. Little code and memory footprint, due to the modular design, while maintaining a simple API to extend
3. Put all the devices interactions under the same mental/use model to facilitate the use by beginners, speeding up the users interest to get new ones and combine them in their projects
4. Having fun building projects with Easyuino as much as I have developing it!!!

## List of Sensors and Devices Supported

### Currently Supported

- RGB Led
- Ultrasonic Module
- GSM Module (currently only SMS services)
- Relay Module 
- Water Detector Sensor
- Water Flow Sensor

### Under Development

- Seven Segments Display
- Soil Moisture/Humidity Sensor

### Future Development

- Photoresistor/Light Sensor
- Flame Sensor
- Infra Red Receiver
- Temperature/Humidity Sensor
- Knock Sensor
- Sound Sensor
- Optical Fingerprint Sensor
- Methane/Gas Sensor
- ...

## Installation

1. If using the latest Arduino Desktop IDE
1.1.

1. Use GitHub download *green* button to get the library as a .zip file
2. Using Arduino IDE got to to menu bar choose **Sketch > Include Library** and select the .zip file downloaded in 1.
3. TO get started using Easyuino look for the usage examples in the section below
4. **[Not Optional]** Have fun!!!

## Getting Started

The examples are in examples folder of the library and hosted in the new Arduino Web Platform where users can see the code and upload it to the board using a browser (Chrome recommended) and a plugin. So below are the links for each device/sensor examples you can follow them to the platform, see the simple guides to build the circuit, run and have fun!!

**Important!!:** When looking for how to use a device look at the examples from the left to right. The left ones are the simpler and have a limited set of features that probably will be enough for beginners. The examples at right normally provide more advanced features that are improvements over the basic ones.

* Simple Sensors/Devices
    - Relay ([Relay](https://github.com/Strabox/Easyuino/wiki/Relay-examples), [Named Relay](https://github.com/Strabox/Easyuino/wiki/Named-Relay-Examples))
    - Led ([RGB led](https://create.arduino.cc/editor/Strabox/34b84db3-edf4-4225-9c7c-f47f43cbe842/preview))
    - Ultrasonic ([Distance Meter](https://github.com/Strabox/Easyuino/wiki/Distance-Meter-examples) , [Distance Meter non-block](https://github.com/Strabox/Easyuino/wiki/Distance-Meter-Non-Block-example), [Distance Meter with temperature](https://github.com/Strabox/Easyuino/wiki/Distance-Meter-Accurate-example))
* Advanced/Complex Devices
    - GSM/GPRS Module (Example coming soon)

## Library Maintenance

The development of the library, including fixes and addition of new sensors/devices, will be done depending on:
- My time availability (Now I am doing my Masters Degree Thesis in Computer Science and Engineering that stoles a good slice of my time)

Important: If you have any question about Easyuino you can contact me !!!

Contact Channels:
- Email: easyuino@gmail.com

## Important Features (Advanced)

### Static Memory Allocation

One of the most important thing in low level programming is efficiency and small memory usage (e.g: Arduino Uno Rev3 has 2KB of SRAM to run the program).

So I decided to use static memory allocation whenever possible to maintain heap fragmentation at bay. Whenever possible I decided to allocate the resources statically and only in special cases use dynamic allocation. This decision limits the API but it is a trade-off to maintain safe programs especially for beginners and at the same time try to use the minimum memory possible. If someone needs more resources can adjust the self-explanatory constants in header files.

### Modular API

Most of Arduino boards have a very little ROM memory to store code (e.g: Arduino Uno Rev3 has 28KB available to store code). To reduce the library footprint I made the API modular explained below with a simple example:

```c++
Relay simpleRelay = Relay();
simpleRelay.doCommonFunction();
//...
RelayAdvanced advancedRelay = RelayAdvanced();
advancedRelay.doCommonFunction();
advancedRelay.doAdvancedFunction();
```

In the example, we can see that the RelayAdvanced can do the same and more than Relay but will have more methods and need more memory. The user only needs to choose the one that offers the minimum functionality it needs.

## API Version System

Major.Middle.Minor (e.g: 1.1.2)

The rules for the 3 digit version system are simple and described next:
1. The first version launched was the 1.0.0
2. The Major number is incremented when there are made huge changes (many features introduced and the library looks very different) **OR** something is changed and breaks the compatibility with the previous version
3. The Middle number is incremented when new functionalities are added (e.g: Relay API supports a new feature)
4. The Minor number is incremented when bugs are fixed or very small and unnoticed changes are made to the library

To more details of the versioning system used: http://semver.org/

## Easyuino History Briefly

I am graduated Computer Scientist and Engineer that loves programming special in C/C++. 
This library started with a necessity to use several sensors in a [personal project](https://github.com/Strabox/SmartCampHouse) and at same time make me practice C/C++ programming and a tiny bit o "low level" programming.
At certain point in the development of the project mentioned I decided that isolate all the interfaces with each sensor was a good idea and created this library to help others use the devices easily to accomplish the same tasks I needed.

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
