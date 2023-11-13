# Homework #2

## Task - Design a control system that simulates a 3-floor elevator using the Arduino platform. 

This assignment involves simulating a 3-floor elevator control system usingLEDs, buttons, and a buzzer with Arduino. By the end of this task, I learned how to use button state change, implement debouncing techniques and coordinate multiple components to represent real-world scenarios.

## Video
<a href="https://youtu.be/pl10T8YX4Jw" target="_blank"><img src="https://img.youtube.com/vi/pl10T8YX4Jw/hqdefault.jpg"></a>

## Requirements
- Arduino Uno
- 4 LEDs (3  for  the  floors  and  1  for  the  elevator’s  operational state)
- 3 Buttons (1 for each floor)
- 4 resistors (1 for each LED)
- 1 buzzer 
- wires

## Implementation details
- The 3 buttons are connected to the Arduino Uno board, each one to a digital pin (2, 3, 4).
- The 3 LEDs are connected to the Arduino Uno board, each one to a digital pin (8, 9, 10).
- The 4th LED is connected to the Arduino Uno board, to a digital pin (12).
- The buzzer is connected to the Arduino Uno board, to a digital pin (13).
- The code then checks if a button is pressed, and if so, it will light up the corresponding LED, and move the elevator to that floor. The tricky part is to make the elevator go through each floor in order, and not skip any floors.

## Code Difficulties

- One part was to make the elevator go through each floor in order, and not skip any floors. I solved this by using a variable to store the target floor, and then checking if the elevator is moving or not. If it is not moving, then it will check if the current floor is the same as the target floor, and if not, it will move to the target floor.
- The biggest issue i had was my lack of logic to work within a while true (void loop()), I tried to structure the code within functions, but encountered issues. Lesson learned, I need to adapt.

## Images
![ye](assets/1.jpg)
