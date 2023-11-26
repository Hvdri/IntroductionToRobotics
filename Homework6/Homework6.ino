#include <LedControl.h>

const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;
const byte matrixSize = 8;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);
byte matrixBrightness = 1;

const int pinX = A0;
const int pinY = A1;

int initialSnakeSize = 1;
int snakeSize = 1;
int snakeX[64];
int snakeY[64];

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

Direction snakeDirection = DOWN;

int foodX;
int foodY;

unsigned long previousMillis = 0;
const long interval = 100;



void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, matrixBrightness);
  lc.clearDisplay(0);

  // Initialize snake position
  snakeX[0] = matrixSize / 2;
  snakeY[0] = matrixSize / 2;

  // Place initial food
  spawnFood();
}

void loop() {
  // Read joystick input
  readJoystick();

  // Update snake position at regular intervals
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Update snake position
    updateSnake();

    // Check for collisions
    if (checkCollision()) {
      // Game over

      endOfGame();
      snakeSize = initialSnakeSize;
      return;
    }

    // check for food
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
      snakeSize++;
      spawnFood();
    }

    displaySnake();
    displayFood();
  }
}

void readJoystick() {
  int xValue = analogRead(pinX);
  int yValue = analogRead(pinY);

  if (xValue < 100) {
    snakeDirection = LEFT;
  } else if (xValue > 900) {
    snakeDirection = RIGHT;
  }

  if (yValue < 100) {
    snakeDirection = UP;
  } else if (yValue > 900) {
    snakeDirection = DOWN;
  }
}

void updateSnake() {
  // Move the snake body
  for (int i = snakeSize - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // Move the snake head based on the direction
  switch (snakeDirection) {
    case RIGHT:
      snakeY[0]--;
      break;
    case LEFT:
      snakeY[0]++;
      break;
    case UP:
      snakeX[0]++;
      break;
    case DOWN:
      snakeX[0]--;
      break;
  }

  // Wrap around the edges
  snakeX[0] = (snakeX[0] + matrixSize) % matrixSize;
  snakeY[0] = (snakeY[0] + matrixSize) % matrixSize;
}

void displaySnake() {
  
  lc.clearDisplay(0);

  // Display the snake
  for (int i = 0; i < snakeSize; i++) {
    lc.setLed(0, snakeX[i], snakeY[i], true);
  }
}

const long flickerInterval = 200;
bool foodFlickerState = false;

void displayFood() {
  flickerFood();
  
  if (!foodFlickerState) {
    lc.setLed(0, foodX, foodY, true);
  }
}

void flickerFood() {
  // Flicker the food at a slower rate
  unsigned long currentMillis = millis();
  static unsigned long foodFlickerPreviousMillis = 0;

  if (currentMillis - foodFlickerPreviousMillis >= flickerInterval) {
    foodFlickerPreviousMillis = currentMillis;

    foodFlickerState = !foodFlickerState;
  }
}

void spawnFood() {
  // Generate random food position
  foodX = random(matrixSize);
  foodY = random(matrixSize);

  // Ensure the food doesn't overlap with the snake
  for (int i = 0; i < snakeSize; i++) {
    if (foodX == snakeX[i] && foodY == snakeY[i]) {
      // If overlap, recursively call spawnFood to try again
      spawnFood();
      return;
    }
  }
}

bool checkCollision() {
  for (int i = 1; i < snakeSize; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      // Reset snake size to initial size
      return true;
    }
  }
  return false;
}

void endOfGame() {
  for(int flash = 0; flash < 3; flash++){

    lc.clearDisplay(0);
    delay(1000);
    // Display the snake body
      for (int i = 1; i < snakeSize; i++) {
        lc.setLed(0, snakeX[i], snakeY[i], true);
    }
    delay(1000);
  }

    lc.clearDisplay(0);
    setup(); // Restart the game
}
