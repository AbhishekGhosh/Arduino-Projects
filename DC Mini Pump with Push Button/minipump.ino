// Define pin numbers for components
#define PUMP_PIN 5        // Pin connected to the 3V DC pump
#define BUTTON_PIN 2      // Pin connected to the push button
#define GREEN_LED_PIN 8   // Pin connected to the green LED indicator
#define RED_LED_PIN 9     // Pin connected to the red LED indicator

// Define variables to store pump state and LED states
volatile bool pumpRunning = false;
bool greenLedState = LOW;
bool redLedState = LOW;

void setup() {
  // Initialize pins
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistor
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  // Attach interrupt to the button pin
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonPressed, FALLING);

  // Turn off pump and LEDs initially
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}

void loop() {
  // Update LED states based on pump state
  digitalWrite(GREEN_LED_PIN, greenLedState);
  digitalWrite(RED_LED_PIN, redLedState);

  // Check if the pump is running and update LED states accordingly
  if (pumpRunning) {
    greenLedState = HIGH; // Turn on green LED
    redLedState = LOW;    // Turn off red LED
    digitalWrite(PUMP_PIN, HIGH); // Turn on the pump
  } else {
    greenLedState = LOW;  // Turn off green LED
    redLedState = HIGH;   // Turn on red LED
    digitalWrite(PUMP_PIN, LOW);  // Turn off the pump
  }
}

// Interrupt service routine for button press
void buttonPressed() {
  // Toggle pump state
  pumpRunning = !pumpRunning;
}
