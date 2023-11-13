# Homework #1

## Task - RGB Led controlled by 3 potentiometers, each one for each color.
Use a separate potentiometer for controlling each color of the RGB LED: Red, Green and Blue.This control must leverage digital electronics.Specifically, you need to  read the potentiometer’s value with Arduino and then write a mapped value to the LED pins.

## Video
<a href="https://youtu.be/34BXTwMJW_8" target="_blank"><img src="assets/thumbnail.jpg"></a>

## Requirements
- Arduino Uno
- 3 potentiometers
- 1 RGB Led
- 3 resistors 
- wires

## Implementation details
- The 3 potentiometers are connected to the Arduino Uno board, each one to an analog pin (A0, A1, A2).
- The RGB Led is connected to the Arduino Uno board, each color to a resistor, then to a digital pin (9, 10, 11).
- The code then calculates the rotation of each potentiometer into the value of brightness for its respective color (A0 - 9, A1 - 10, A2 - 11).


## Images
![off](assets/4.jpg)
![red](assets/1.jpg)
![blue](assets/2.jpg)
![green](assets/3.jpg)
