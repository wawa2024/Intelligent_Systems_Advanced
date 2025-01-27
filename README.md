# Arduino weather data project

## Circuit schematics ([link](https://github.com/lamiika/arduino_weather_data_project/tree/main/schematics))

- [Tinkercad design image of the entire circuit](https://github.com/lamiika/arduino_weather_data_project/blob/main/schematics/wind_data_circuit.png)
- [Wind speed schematic](https://github.com/lamiika/arduino_weather_data_project/blob/main/schematics/wind_speed_schematic.PNG)
- [Wind direction schematic](https://github.com/lamiika/arduino_weather_data_project/blob/main/schematics/wind_direction_schematic.png)
- [4x4 keypad control circuit using 2 pins](https://github.com/lamiika/arduino_weather_data_project/blob/main/schematics/keypad_io.png)

## Software ([link](https://github.com/lamiika/arduino_weather_data_project/tree/main/src/main))

The code is separated to different modules that each are initialized in the void setup()-function of the [main.ino](https://github.com/lamiika/arduino_weather_data_project/blob/main/src/main/main.ino)-file.

## Description

This project connects an Arduino Nano to a wind speed and wind direction signal from a weather station. There is an intermediate circuit that we designed to filter out noise from the signal and to amplify the voltage to 5V for Arduino's analog pins. The Arduino processes the signal and sends the data by using MQTT via ethernet to a Raspberry Pi that runs the MQTT broker server. 

The Raspberry Pi server and the weather station were existing infrastructure that we used and thus were outside the scope of this project.

There is also an [additional music playing feature](https://github.com/lamiika/arduino_weather_data_project/tree/main/src/main/include) taken from my solo project [music_box.](https://github.com/lamiika/music_box) This feature makes the project take up the entirety of Arduino Nano's memory. If anything more is added to the code, the software starts to break.
