const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;
const int buzzerPin = 3;

const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;

const int segSize = 8;
int index = segSize - 1;  // Set pinDP as the initially selected LED

bool commonAnode = false;  // Modify if you have common anode
const int noOfDigits = 10;
byte state = HIGH;
byte dpState = LOW;
volatile byte swState = LOW;
bool ledState = LOW;
byte lastSwState = LOW;

bool joyMoved = false;
int digit = 0;
int minThreshold = 400;
int maxThreshold = 600;
int xValue = 0;
int yValue = 0;
int oldIndex = 0;

int previousIndex = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 1000;  // Debounce delay in milliseconds
unsigned long debounceDelayPress = 100;

unsigned long buttonPressTime = 0;

unsigned long previousDotMillis = 0;
unsigned long dotInterval = 500;  // Flicker interval in milliseconds
bool dotState = false;

int buzzerNoteHz = 261.63;
int buzzTime = 500;

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
bool ledStates[segSize];  // Array to store the LED states

void setup() {
  // Initialize all the pins
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(buzzerPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pinSW), buttonInterrupt, CHANGE);
  // TODO: Check if commonAnode should be modified here
  if (commonAnode == true) {
    state = !state;
  }

  Serial.begin(9600);
}

void buttonInterrupt() {
  swState = digitalRead(pinSW);
}

void flicker(int currentMillis) {
  if (currentMillis - previousDotMillis >= dotInterval) {
    previousDotMillis = currentMillis;
    dotState = !dotState;
  }
}

void move() {
  oldIndex = index;
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  if (xValue < minThreshold && joyMoved == false) {
      // Move left
      if (index == 0 || index == 1)  // A || B
        index = 5;                   // F

      if (index == 2 || index == 3)  // C || D
        index = 4;                   // E

      if (index == 7)  // Dp
        index = 2;     // C

      joyMoved = true;
    }
    if (xValue > maxThreshold && joyMoved == false) {
      // Move right
      if (index == 2) // C
        index = 7; // DP

      if (index == 0 || index == 5)  // A || F
        index = 1;
      if (index == 4 || index == 3)  // E || D
        index = 2;

      joyMoved = true;
    }
    if (yValue < minThreshold && joyMoved == false) {
      // Move up
      if (index == 6 || index == 1 || index == 5)  // G B F
        index = 0;

      if (index == 3)  // D
        index = 6;


      if (index == 4)  // E
        index = 5;     // F

      if (index == 2)  // C
        index = 1;     // B


    
      joyMoved = true;
    }
    if (yValue > maxThreshold && joyMoved == false) {
      // Move down


      if (index == 6 || index == 4 || index == 2)
        index = 3;

      if (index == 0)
        index = 6;

      if (index == 1)  // B
        index = 2;     // C

      if (index == 5)  // F
        index = 4;     // E

      joyMoved = true;
    }

    if(xValue >= minThreshold && xValue <= maxThreshold &&
       yValue >= minThreshold && yValue <= maxThreshold ) {
        joyMoved = false;
    }
}

void action(int currentMillis) {
  
  if (currentMillis - lastDebounceTime >= debounceDelayPress) {
    if (swState != lastSwState) {
      // Check if the button has been held for 2 seconds
      if (swState == HIGH && currentMillis - buttonPressTime >= 2000) {
        tone(buzzerPin, buzzerNoteHz, buzzTime);
        Serial.println("Button held for 2 seconds");
        resetLEDs();  // Reset all LEDs when the button is held for 2 seconds
      } 
      
      if(swState == LOW) {
          tone(buzzerPin, buzzerNoteHz / 2, buzzTime / 2);
          buttonPressTime = currentMillis;
          ledStates[index] = !ledStates[index];             // Toggle LED state when the button is pressed
          digitalWrite(segments[index], ledStates[index]);  // Set the LED state
          Serial.println(ledStates[index] ? "LED ON" : "LED OFF");
      }

      lastDebounceTime = currentMillis;
    }
  }

  lastSwState = swState;

  // Turn off the previous LED
  if (oldIndex != index) {
    digitalWrite(segments[oldIndex], ledStates[oldIndex]);
  }

  // Flicker the currently selected LED
  digitalWrite(segments[index], dotState);
}

void resetLEDs() {
  for (int i = 0; i < segSize; i++) {
    ledStates[i] = LOW;
    digitalWrite(segments[i], LOW);
  }
  index = segSize - 1;
}

void loop() {
  unsigned long currentMillis = millis();

  flicker(currentMillis);

  move();

  action(currentMillis);
}