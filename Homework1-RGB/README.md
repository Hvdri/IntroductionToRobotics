# Homework #1

## Task - RGB Led controlled by 3 potentiometers, each one for each color.
Use a separate potentiometer for controlling each color of the RGB LED: Red, Green and Blue.This control must leverage digital electronics.Specifically, you need to  read the potentiometer’s value with Arduino and then write a mapped value to the LED pins.

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

## Code 
```c
const int redPin = 9;    // Red LED pin
const int greenPin = 10;  // Green LED pin
const int bluePin = 11;   // Blue LED pin

const int redPotPin = A0;    // Potentiometer for Red color
const int greenPotPin = A1;  // Potentiometer for Green color
const int bluePotPin = A2;   // Potentiometer for Blue color

const int minPotValue = 0;  // Minimum potentiometer value
const int maxPotValue = 1023;  // Maximum potentiometer value

const int minLedBrightness = 0;  // Minimum LED brightness
const int maxLedBrightness = 255;  // Maximum LED brightness

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Read the potentiometer values
  int redValue = analogRead(redPotPin);
  int greenValue = analogRead(greenPotPin);
  int blueValue = analogRead(bluePotPin);


  // Map the potentiometer values to the LED brightness
  int redBrightness = map(redValue, minPotValue, maxPotValue, minLedBrightness, maxLedBrightness);
  int greenBrightness = map(greenValue, minPotValue, maxPotValue, minLedBrightness, maxLedBrightness);
  int blueBrightness = map(blueValue, minPotValue, maxPotValue, minLedBrightness, maxLedBrightness);

  if(redBrightness < 15)
    redBrightness = 0;
  if(greenBrightness < 15)
    greenBrightness = 0;
  if(blueBrightness < 15)
    blueBrightness = 0;

  // Update the LED colors
  analogWrite(redPin, redBrightness);
  analogWrite(greenPin, greenBrightness);
  analogWrite(bluePin, blueBrightness);
}
}
```

## Video
<a href="https://youtu.be/34BXTwMJW_8" target="_blank"><img src="assets/thumbnail.jpg"></a>

## Images
![off](assets/4.jpg)
![red](assets/1.jpg)
![blue](assets/2.jpg)
![green](assets/3.jpg)
