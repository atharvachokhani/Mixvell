// Mixvell Motor Cycling Test Sketch
// This sketch validates the connection and functionality of 
// six relay modules/motors connected to the specified Arduino pins.

// --- Pin Definitions (Based on user's configuration) ---
// Note: Relays often use LOW signal to activate/turn ON the motor.
// We will use HIGH/LOW assuming a standard active-LOW relay module.

const int MOTOR_PINS[] = {
  12, // Pump 1: Digital Pin 12
  11, // Pump 2: Digital Pin 11
  10, // Pump 3: Digital Pin 10
  9,  // Pump 4: Digital Pin 9
  8,  // Pump 5: Digital Pin 8
  7   // Pump 6: Digital Pin 7
};

const int NUM_MOTORS = sizeof(MOTOR_PINS) / sizeof(MOTOR_PINS[0]);

// --- Configuration ---
// Duration to keep the motor ON (in milliseconds)
const long MOTOR_ON_TIME = 2000; 
// Delay between turning one motor OFF and the next motor ON (in milliseconds)
const long INTER_MOTOR_DELAY = 1000; 

// --- Setup Function ---
void setup() {
  // Initialize all motor pins as outputs
  for (int i = 0; i < NUM_MOTORS; i++) {
    pinMode(MOTOR_PINS[i], OUTPUT);
    // Ensure all motors are OFF initially. 
    // We assume ACTIVE-LOW relays, so setting HIGH turns them OFF.
    digitalWrite(MOTOR_PINS[i], HIGH);
  }

  Serial.begin(9600);
  Serial.println("Mixvell Motor Test Starting...");
  Serial.println("Motors will cycle through D12 to D7.");
  delay(1000); // Wait a second before starting
}

// --- Main Loop Function ---
void loop() {
  // Iterate through each motor pin
  for (int i = 0; i < NUM_MOTORS; i++) {
    int currentPin = MOTOR_PINS[i];
    
    Serial.print("Testing Pump ");
    Serial.print(i + 1); // Display 1-based index (Pump 1, 2, ...)
    Serial.print(" on Pin D");
    Serial.print(currentPin);
    Serial.println("... ON");

    // 1. Turn the current motor ON (assuming active-LOW relay)
    digitalWrite(currentPin, LOW);
    
    // Wait for the motor to run for the specified time
    delay(MOTOR_ON_TIME);
    
    Serial.print("Pump ");
    Serial.print(i + 1);
    Serial.println("... OFF");

    // 2. Turn the motor OFF (assuming active-LOW relay)
    digitalWrite(currentPin, HIGH);

    // Pause before activating the next motor
    delay(INTER_MOTOR_DELAY);
  }

  Serial.println("--- Cycle Complete. Restarting in 3 seconds. ---");
  delay(3000); // Long delay before repeating the cycle
}
