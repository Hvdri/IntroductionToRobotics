#define SENSOR_SETTINGS 1
#define RESET_LOGGER_DATA 2
#define SYSTEM_STATUS 3
#define RGB_LED_CONTROL 4

#define BACK 0
#define YES 1
#define NO 2

int userChoice = -1;
String inputString = "";
int currentSubMenu = 0;  // Added variable to track the current submenu
bool inSubMenu = false; // Added flag to track if the user is in a submenu
bool menu = false;

// Function prototypes
void printMenu();
void handleUserInput();
void sensorSettingsMenu();
void resetLoggerDataMenu();
void systemStatusMenu();
void rgbLedControlMenu();

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (menu == false) {
    printMenu();
    menu = true;
  }

  handleUserInput();
}

void printMenu() {
  Serial.println("\nMenu:");
  Serial.println("1. Sensor Settings");
  Serial.println("2. Reset Logger Data");
  Serial.println("3. System Status");
  Serial.println("4. RGB LED Control");
  Serial.println("0. Back");
  Serial.println("Enter your choice:");
}

void handleUserInput() {
  if (Serial.available()) {
    char incomingByte = Serial.read();
    if (incomingByte == '\n') {
      // Handle the user's choice
      int choice = inputString.toInt();
      if (!inSubMenu) {
        // If not in a submenu, process the choice as main menu option
        switch (choice) {
          case SENSOR_SETTINGS:
            currentSubMenu = SENSOR_SETTINGS;
            inSubMenu = true;
            sensorSettingsMenu();
            break;
          case RESET_LOGGER_DATA:
            currentSubMenu = RESET_LOGGER_DATA;
            inSubMenu = true;
            resetLoggerDataMenu();
            break;
          case SYSTEM_STATUS:
            currentSubMenu = SYSTEM_STATUS;
            inSubMenu = true;
            systemStatusMenu();
            break;
          case RGB_LED_CONTROL:
            currentSubMenu = RGB_LED_CONTROL;
            inSubMenu = true;
            rgbLedControlMenu();
            break;
          case BACK:
            menu = false;
            break;
          default:
            Serial.println("Invalid choice. Please enter a valid option.");
            break;
        }
      } else {
        // If in a submenu, process the choice based on the current submenu
        switch (currentSubMenu) {
          case SENSOR_SETTINGS:
            // Process submenu choices for SENSOR_SETTINGS
            // (Add your code here)
            break;
          case RESET_LOGGER_DATA:
            // Process submenu choices for RESET_LOGGER_DATA
            // (Add your code here)
            break;
          case SYSTEM_STATUS:
            // Process submenu choices for SYSTEM_STATUS
            // (Add your code here)
            break;
          case RGB_LED_CONTROL:
            // Process submenu choices for RGB_LED_CONTROL
            // (Add your code here)
            break;
          default:
            Serial.println("Invalid submenu choice.");
            break;
        }
        inSubMenu = false; // Reset the submenu flag after processing the choice
      }

      // Print the user's choice
      if (choice >= 0 && choice != BACK) {
        Serial.println("You chose: " + String(choice));
      }

      // Reset inputString for the next input
      inputString = "";
    } else {
      // Accumulate characters until newline is received
      inputString += incomingByte;
    }
  }
}

void sensorSettingsMenu() {
  Serial.println("\n    Sensor Settings Menu:");
  Serial.println("    1. Sensors Sampling Interval");
  Serial.println("    2. Ultrasonic Alert Threshold");
  Serial.println("    3. LDR Alert Threshold");
  Serial.println("    0. Back");
  Serial.println("    Enter your choice:");
}

void resetLoggerDataMenu() {
  Serial.println("\n    Reset Logger Data Menu:");
  Serial.println("    Are you sure?");
  Serial.println("    1. Yes");
  Serial.println("    2. No");
  Serial.println("    0. Back");
  Serial.println("    Enter your choice:");
}

void systemStatusMenu() {
  Serial.println("\n    System Status Menu:");
  Serial.println("    1. Current Sensor Readings");
  Serial.println("    2. Current Sensor Settings");
  Serial.println("    3. Display Logged Data");
  Serial.println("    0. Back");
  Serial.println("    Enter your choice:");
}

void rgbLedControlMenu() {
  Serial.println("\n    RGB LED Control Menu:");
  Serial.println("    1. Manual Color Control");
  Serial.println("    2. LED: Toggle Automatic ON/OFF");
  Serial.println("    0. Back");
  Serial.println("    Enter your choice:");
}
