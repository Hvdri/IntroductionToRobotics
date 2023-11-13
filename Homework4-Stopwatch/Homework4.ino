// Define connections to the shift register
const int latchPin = 11;  // Connects to STCP (latch pin) on the shift register
const int clockPin = 10;  // Connects to SHCP (clock pin) on the shift register
const int dataPin = 12;   // Connects to DS (data pin) on the shift register
// Define connections to the digit control pins for a 4-digit display
const int segD1 = 4;
const int segD2 = 5;
const int segD3 = 6;
const int segD4 = 7;
// Store the digits in an array for easy access
int displayDigits[] = { segD1, segD2, segD3, segD4 };
const int displayCount = 4;  // Number of digits in the display
// Define the number of unique encodings (0-9, A-F for hexadecimal)
const int encodingsNumber = 10;
// Define byte encodings for the hexadecimal characters 0-9
byte byteEncodings[encodingsNumber] = {
  //A B C D E F G DP
  B11111100,  // 0
  B01100000,  // 1
  B11011010,  // 2
  B11110010,  // 3
  B01100110,  // 4
  B10110110,  // 5
  B10111110,  // 6
  B11100000,  // 7
  B11111110,  // 8
  B11110110,  // 9
};

// Variables for controlling the display update timing
unsigned long lastIncrement = 0;
unsigned long delayCount = 100;  // Delay between updates (milliseconds)
unsigned long number = 0;        // The number being displayed

const int startStopButton = 2;
const int lapButton = 3;
const int resetButton = 8;
const int buzzerPin = 13;

volatile bool displayRunning = false;
unsigned long currentTime = millis();

const int lapArraySize = 4;
int lapTimes[lapArraySize];
int lapIndex = 0;

static unsigned long lastLapButtonPressTime = 0;
static bool lapButtonState = HIGH;  // HIGH means not pressed, LOW means pressed
const int buzzerFrec = 440;
const int buzzerDuration = 100;

void setup() {
  // Initialize the pins connected to the shift register as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  // Initialize digit control pins and set them to LOW (off)
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }

  pinMode(startStopButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(startStopButton), buttonInterrupt, CHANGE);

  pinMode(lapButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(lapButton), lapButtonInterrupt, CHANGE);

  pinMode(resetButton, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT);

  // Begin serial communication for debugging purposes
  Serial.begin(9600);
}

void loop() {
  if (displayRunning) {
    // Increment the number and update the display only if it's allowed to run
    if (millis() - lastIncrement > delayCount) {
      number++;
      number %= 10000;  // Wrap around after 9999
      lastIncrement = millis();
    }
    // Display the incremented number on the 7-segment display using multiplexing
  }
  writeNumber(number);
  if (digitalRead(resetButton) == LOW) {
    tone(buzzerPin, buzzerFrec, buzzerDuration);
    number = 0;
    displayRunning = false;
    lastIncrement = millis();
  }
}


void lapButtonInterrupt() {
  // Interrupt handler for the lap button
  tone(buzzerPin, buzzerFrec, buzzerDuration);

  int lapButtonReading = digitalRead(lapButton);

  if (lapButtonReading != lapButtonState) {
    // Update the button state if it has changed
    lastLapButtonPressTime = currentTime;
    lapButtonState = lapButtonReading;

    // Process the button press only if it's a LOW (pressed) state
    if (lapButtonState == LOW && displayRunning) {
      recordLapTime(number);
    } else if (lapButtonState == LOW && !displayRunning) {
      displayLapTime();
    }
  }
}

void recordLapTime(int number) {
  // Record lap time
  lapTimes[lapIndex] = number;
  lapIndex = (lapIndex + 1) % lapArraySize;
}

void displayLapTime() {
  // Display lap time
  number = lapTimes[lapIndex];
  lapIndex = (lapIndex + 1) % lapArraySize;
  writeNumber(number);
}

void buttonInterrupt() {
  // Interrupt handler for the button
  tone(buzzerPin, buzzerFrec, buzzerDuration);
  // Toggle the state of displayRunning when the button is pressed
  if (digitalRead(startStopButton) == LOW) {
    displayRunning = !displayRunning;
    lastIncrement = millis();
  }
}

void writeReg(int digit) {
  // Prepare to shift data by setting the latch pin low
  digitalWrite(latchPin, LOW);
  // Shift out the byte representing the current digit to the shift register
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  // Latch the data onto the output pins by setting the latch pin high
  digitalWrite(latchPin, HIGH);
}

void activateDisplay(int displayNumber) {
  // Turn off all digit control pins to avoid ghosting
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  // Turn on the current digit control pin
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeNumber(int number) {
  // Initialize necessary variables for tracking the current number and digit position
  int currentNumber = number;
  int displayDigit = 3;  // Start with the least significant digit
  int lastDigit = 0;
  int decimalPoint = 1;  // The position of the decimal point, starting from the right

  // Loop through each digit of the current number
  while (currentNumber != 0 || displayDigit >= 0) {
    // Extract the last digit of the current number
    lastDigit = currentNumber % 10;

    // Activate the current digit on the display
    activateDisplay(displayDigit);

    // Output the byte encoding for the last digit to the display
    if (displayDigit == 2) {
      // Set the decimal point for the third digit (seconds)
      writeReg(byteEncodings[lastDigit] + 1);
    } else {
      // Output the byte encoding without the decimal point
      writeReg(byteEncodings[lastDigit]);
    }

    // Move to the next digit and adjust the decimal point position
    displayDigit--;
    decimalPoint++;

    // Update 'currentNumber' by removing the last digit
    currentNumber /= 10;

    // Clear the display to prevent ghosting between digit activations
    writeReg(B00000000);  // Clear the register to avoid ghosting
  }
}
