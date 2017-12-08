# Easyuino [![Build Status](https://travis-ci.org/Strabox/Easyuino.svg?branch=master)](https://travis-ci.org/Strabox/Easyuino)

## Table of Contents

- [What is Easyuino?](https://github.com/Strabox/Easyuino#what-is-easyuino?)
- [List of Sensors and Devices](https://github.com/Strabox/Easyuino#list-of-sensors-and-devices)
	* [Currently Supported](https://github.com/Strabox/Easyuino#currently-supported)
	* [Under Development](https://github.com/Strabox/Easyuino#under-development)
	* [Future Development](https://github.com/Strabox/Easyuino#future-development)
- [Getting Started](https://github.com/Strabox/Easyuino#getting-started)
	* [Installation](https://github.com/Strabox/Easyuino#installation)
	* [Usage Examples](https://github.com/Strabox/Easyuino#usage-examples)
	* [API Documentation and Troubleshoot](https://github.com/Strabox/Easyuino#api-documentation-and-troubleshoot)
- [Project Structure](https://github.com/Strabox/Easyuino#project-structure)
- [Library Maintenance and Contacts](https://github.com/Strabox/Easyuino#library-maintenance-and-contacts)
- [Important Features (Advanced)](https://github.com/Strabox/Easyuino#important-features-(advanced))
	* [Static Memory Allocation](https://github.com/Strabox/Easyuino#static-memory-allocation)
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
- Seven Segments Display [Hardware Supported: TM1637 Driver]
- Ultrasonic Module [Hardware Supported: HC-SR03, HC-SR04, HC-SR05]
- Buttons
- Relay Module 
- Water Detector Sensor
- Water Flow Sensor/Meter (Can be used for air and other fluids) [Hardware Supported: YF-DN40]
- GSM Module (currently SMS services only) [Hardware Supported: GSM900 Chipset]

**Note:** The hardware devices supported could be more than the specified. I only put there the tested ones.
**Note2:** The devices that doesn't have [Hardware supported] tag it is due to its simplicity.

### Under Development

- Radio Frequency Communication Module
- Soil Moisture/Humidity Sensor

### Future Development

- Photoresistor/Light Sensor
- Flame Sensor
- Infra Red Receiver
- Temperature/Humidity Sensor
- Sound Sensor
- Optical Fingerprint Sensor
- Methane/Gas Sensor
- ...

## Getting Started

### Installation

- If using the Arduino Desktop IDE
	1. Go to the menu **Sketch > Include Library > Manage Libraries**
	2. Search for Easyuino in **Search Bar**
	3. Click on the Easyuino box
	4. Select the lastest version and click in **Install Button**
	5. Go to the menu **Sketch > Include Library**
	6. Scroll down until you find Easyuino, click on it and DONE
- If using the [Arduino Web IDE](https://create.arduino.cc/editor)
	1. Go to the **Libraries** menu in left
	2. Search for Easyuino in **Search Bar**
	3. Put the mouse hover Easyuino box and click **Include** and DONE (this will automatically include Easyuino in your sketch)

### Usage Examples

The examples are in examples folder of the library and hosted in the new [Arduino Web Platform](https://create.arduino.cc/editor) where users can see the code and upload it to the board using a browser (Chrome recommended) and a plugin. So below are the links for each device/sensor examples you can follow them to the platform, see the simple guides to build the circuit, run and have fun!!

**Important!!:** When looking for how to use a device look at the examples from the left to right. The left ones are the simpler and have a limited set of features that probably will be enough for beginners. The examples at right normally provide more advanced features that are improvements over the basic ones.

* Simple Sensors/Devices
    - Relay: [Turn On and Off a bulb](https://create.arduino.cc/editor/Strabox/1834908b-32db-4db2-aedc-e07a33c67559/preview), [Turn on and off a bulb with a identifier](https://create.arduino.cc/editor/Strabox/0035db7d-95da-407c-a858-cda62968412d/preview)
    - Led: [Color festival with RGB led](https://create.arduino.cc/editor/Strabox/34b84db3-edf4-4225-9c7c-f47f43cbe842/preview)
    - Ultrasonic Module: [Measure distance](https://create.arduino.cc/editor/Strabox/86378038-2287-437a-b7a8-fa9fb0788ea7/preview) , [Measure distance without stop Arduino](https://create.arduino.cc/editor/Strabox/ab13f15d-e830-4430-b1b5-0a7726e60b13/preview), [Measure distance considering temperature](https://create.arduino.cc/editor/Strabox/497ecf13-17b4-4bd3-94d0-9435eca87bbe/preview)
	- Water Detector Sensor: [How soaked is ?](https://create.arduino.cc/editor/Strabox/e732834f-9262-48f5-982b-df51f3ffe7ed/preview)
	- Water Flow Sensor: [Water is Flowing?](https://create.arduino.cc/editor/Strabox/3ac395de-bc8e-4b64-98d9-b5f33a563cc9/preview), [How much water is flowing?](https://create.arduino.cc/editor/Strabox/e4677503-b766-4b37-87ac-247b1621729d/preview)
* Advanced/Complex  Sensors/Devices
    - GSM/GPRS Module (currently only SMS services): [Send, Receive and delete SMS](https://create.arduino.cc/editor/Strabox/753bbeab-f2be-49b7-9caf-9a6b0f965575/preview), [Control who can send SMS to the Arduino](https://create.arduino.cc/editor/Strabox/ef0dfcde-b93a-4a7c-9611-94a2f186fc0d/preview)

### API Documentation and Troubleshoot

[Here](https://strabox.github.io/Easyuino/) you can consult the detailed documentation for the latest version of the Easyuino API. The documentation in the link is the same that is in the **\docs\html** folder of the latest Easyuino release.

If you have an old version you can go to the **\docs\html** folder in the library and consult the documentation from that version opening the index.html file in your favorite browser.

If the API documentantion is not enough to clarify you or found a bug [contact me.](https://github.com/Strabox/Easyuino#library-maintenance)

## Project Structure

- **/docs** contains the documentation of the API in HTML and LaTeX 
- **/examples** contains usage examples of the API
- **/extras** contains materials used to develop the library (e.g: devices guides, schemes, ...)
- **/src** contains the source code of the library
- *.releaseGuide* describes step-by-step how to release a new version of Easyuino
- *.travis.yml* describes the script to test Easyuino in CI [Travis Platform](https://travis-ci.org/)
- *Doxyfile* is used as input to [Doxygen](http://www.doxygen.org) tool in order to generate the API documentation from the source code

## Library Maintenance and Contacts

The maintenance/development of the library, including fixes and addition of new sensors/devices, will be done depending on:
- My time availability (Now I am doing my Masters Degree Thesis in Computer Science and Engineering that stoles a good slice of my time)

**Important:** If you have any question about Easyuino you can contact me!!

Contact Channels:
- Email: easyuino@gmail.com

## Contributing

TODO

## Important Features (Advanced)

### Static Memory Allocation

One of the most important thing in low level programming is efficiency and small memory usage (e.g: Arduino Uno Rev3 has 2KB of SRAM to run the program).

So I decided to use static memory allocation whenever possible to maintain heap fragmentation at bay. Whenever possible I decided to allocate the resources statically and only in special cases use dynamic allocation. This decision limits the API but it is a trade-off to maintain safe programs specially for beginners and at the same time try to use the minimum memory possible. If someone needs more resources can adjust the self-explanatory constants in header files.

## API Versioning System

Major.Middle.Minor (e.g: 1.1.2)

The resumed rules for the versions are simple and described next:
- The first public version launched was the 1.0.0
- The Major number is incremented when there are made huge changes (many features introduced and the library looks very different) **OR** something is changed and breaks the compatibility with the previous version
- The Middle number is incremented when new functionalities are added (e.g: Relay API supports a new feature)
- The Minor number is incremented when bugs are fixed or very small and unnoticed changes are made to the library

To more details of the versioning system used consult: http://semver.org/

## Easyuino History Briefly

I am graduated Computer Scientist and Engineer that loves programming special in C/C++. 
This library started with a necessity to use several sensors in a [personal project to build a remote controlled water tank](https://github.com/Strabox/SmartCampHouse) and at same time make me practice C/C++ programming and a tiny bit o "low level" programming.
At certain point in the development of the project mentioned I decided that isolate all the interfaces with each sensor was a good idea. I created this library to help others use the devices easily and focus on the system functionalities without need to worry with devices details.

## License 

This project is licensed under the MIT License - see the LICENSE.md file for details
