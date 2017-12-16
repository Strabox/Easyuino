# Easyuino [![Build Status](https://travis-ci.org/Strabox/Easyuino.svg?branch=master)](https://travis-ci.org/Strabox/Easyuino)

## Table of Contents

- [What is Easyuino?](https://github.com/Strabox/Easyuino#what-is-easyuino-)
- [List of Sensors and Devices Supported](https://github.com/Strabox/Easyuino#list-of-sensors-and-devices-supported)
	* [Currently Supported](https://github.com/Strabox/Easyuino#currently-supported)
	* [Under Development](https://github.com/Strabox/Easyuino#under-development)
	* [Future Development](https://github.com/Strabox/Easyuino#future-development)
- [Getting Started](https://github.com/Strabox/Easyuino#getting-started)
	* [Installation](https://github.com/Strabox/Easyuino#installation)
	* [Usage Examples](https://github.com/Strabox/Easyuino#usage-examples)
	* [API Documentation and Troubleshoot](https://github.com/Strabox/Easyuino#api-documentation-and-troubleshoot)
- [Project Structure](https://github.com/Strabox/Easyuino#project-structure)
- [Contribution and Maintenance](https://github.com/Strabox/Easyuino#contribution-and-maintenance)
- [Important Features (Advanced)](https://github.com/Strabox/Easyuino#important-features-advanced)
	* [Static Memory Allocation](https://github.com/Strabox/Easyuino#static-memory-allocation)
- [API Versioning System](https://github.com/Strabox/Easyuino#api-versioning-system)
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
- Buttons
- Relay Module 
- Water Detector Sensor
- Seven Segments Display [Hardware Supported: TM1637 Driver]
- Ultrasonic Module [Hardware Supported: HC-SR03, HC-SR04, HC-SR05]
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
	6. Scroll down until you find Easyuino, click on it and it is DONE
- If using the [Arduino Web IDE](https://create.arduino.cc/editor)
	1. Go to the **Libraries** menu in left
	2. Search for Easyuino in **Search Bar**
	3. Put the mouse hover Easyuino box and click **Include** and it is DONE

### Usage Examples

The examples are in examples folder of the library and hosted in the new [Arduino Web IDE](https://create.arduino.cc/editor) where users can see the code and upload it to the board using a browser (Chrome recommended) and a plugin.

Go to the Arduino Web IDE make the registration, search for Easyuino library and import the examples and upload them directly to your board all of this from your browser.

If you don't want use Arduino Web IDE check the examples folder of the library.

### API Documentation and Troubleshoot

[Here](https://strabox.github.io/Easyuino/) you can consult the detailed documentation for the latest version of the Easyuino API. The documentation in the link is the same that is in the **/docs** folder of the latest Easyuino release.

If you have an old version you can go to the **/docs** folder in the library and consult the documentation from that version opening the index.html file in your favorite browser.

If the API documentantion is not enough to clarify you or found a bug [contact me](https://github.com/Strabox/Easyuino#contribution-and-maintenance).

## Project Structure

- **/docs** contains the documentation of the API in HTML
- **/examples** contains usage examples of the API (same examples as the ones presented above)
- **/extras** contains materials used to develop the library (e.g: devices guides, electronic schemes, ...)
- **/src** contains the source code of the library
- *.releaseGuide* describes step-by-step how to release a new version of Easyuino
- *.travis.yml* script to test Easyuino in CI [Travis Platform](https://travis-ci.org/)
- *Doxyfile* is used as input to [Doxygen](http://www.doxygen.org) tool in order to generate the API documentation from the source code

## Contribution and Maintenance

If you want contribute you can:
- Report bugs using issues mechanism of GitHub or sending an email. 
- Forking, enhancing the library and submiting a pull request.
- Provide constructive ideas and suggestions via issues or email. 

**All the help is welcome!!**

**Important:** If you have any question about Easyuino you can contact me via email or issues system.

Contact Channels:
- Email: easyuino@gmail.com

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

This project is licensed under the MIT License - see the LICENSE.md file for details.
