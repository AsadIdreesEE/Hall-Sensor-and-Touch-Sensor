const int sensorPin = 2; // Speed sensor signal connected to digital pin 2
volatile unsigned long pulseCount = 0; // Variable to count the number of pulses
unsigned long previousMillis = 0;
float speed = 0.0; // Variable to store calculated speed
const unsigned long interval = 1000; // Interval for speed calculation (in milliseconds)

// Debounce handling
const unsigned long debounceInterval = 10; // Debounce interval in milliseconds
volatile unsigned long lastDebounceTime = 0; // Variable to store the last debounce time

void setup() {
  pinMode(sensorPin, INPUT_PULLUP); // Set the sensor pin as an input with an internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(sensorPin), countPulse, FALLING); // Interrupt on falling edge of sensor pin
  Serial.begin(115200); // Initialize serial communication at 115200 bits per second
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  // If the interval has passed, calculate the speed
  if (currentMillis - previousMillis >= interval) {
    detachInterrupt(digitalPinToInterrupt(sensorPin)); // Disable interrupts while calculating

    // Calculate speed in revolutions per second (RPS)
    speed = (pulseCount * 60.0) / 20.0; // Assuming 20 pulses per revolution

    //Serial.print("Speed: ");
    Serial.println(speed);
    //Serial.println(" RPM (Revolutions Per Minute)");

    pulseCount = 0; // Reset pulse count
    previousMillis = currentMillis; // Update the previous time

    attachInterrupt(digitalPinToInterrupt(sensorPin), countPulse, FALLING); // Re-enable interrupts
  }
}

// Interrupt service routine to count pulses
void countPulse() {
  unsigned long currentDebounceTime = millis();
  if ((currentDebounceTime - lastDebounceTime) > debounceInterval) { // Debounce check
    pulseCount++; // Increment pulse count
    lastDebounceTime = currentDebounceTime; // Update last debounce time
  }
}
