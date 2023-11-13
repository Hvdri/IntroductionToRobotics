# Homework #4

## Task - Use a 4 Digit 7 Segment Display and a Shift Register to implement a stopwatch timer.

In this assignment, using the 4 digit 7 segment display and 3 buttons, you should implement a stopwatch timer that counts in 10ths of a second and has a save lap functionality (similar to most basic stopwatch functionson most phones).

## Video
<a href="https://youtu.be/vjKBlgXtpJw" target="_blank"><img src="https://img.youtube.com/vi/vjKBlgXtpJw/hqdefault.jpg"></a>

1. Display shows ”000.0”.  When pressing theStartbutton, the timer should start.

2. During timer counter, each time you press the lap button, you should save that timer’s value in memory (not persistent, it is OK to be deleted upon reset), up to 4 laps (or more if you want); pressing the 5th time should override the 1st saved one. If you press the resetbutton while timer works, nothing happens. If you press the pausebutton, the timer stops.

3. In Pause Mode, the lap flag button doesn’t work anymore. Pressing the reset button resets you to 000.0.

4. After reset, you can now press the flag buttons to cycle through the lap times. Each time you press the flag button, it takes you to the next saved lap. Pressing it continuously should cycle you through it continuously. Pressing the reset button while in this state resets all your flags and takes the timer back to ”000.0”.

## Requirements
- Arduino Uno
- 4 digit 7 segment display
- 1 shift register
- 3 buttons
- buzzer
- 8 resistors 
- wires


## Implementation details
- The 4 digit segment display is connected to the Arduino board as follows (Arduino Pin, Display Pin): (4, D1), (5, D2), (6, D3), (7, D4). 
- The shift register is connected to the Arduino board as follows (Arduino Pin, Shift Register Pin): (10, SHCP), (11, STCP), (12, DS), (GND, GND), (5V, VCC), (5V, MR), (GND, OE).
- The 4 digit segment display is connected to the shift register as follows (Display Pin, Shift Register Pin): (A, Q7), (B, Q6), (C, Q5), (D, Q4), (E, Q3), (F, Q2), (G, Q1), (DP, Q0). *Use 220/330 ohm resistors!*
- The buttons are connected to the Arduino board as follows (Arduino Pin, Button Pin): (2, Start/Stop), (3, Lap), (8, Reset).
- The buzzer is connected to the Arduino board (13, Buzzer).

## Code Difficulties

- I did not have any difficulties with this assignment.

## Images
![ye](assets/1.jpg)
