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
