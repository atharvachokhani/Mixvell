#include <Arduino.h>

// Pump pins
const int pump1 = 2;
const int pump2 = 3;
const int pump3 = 4;
const int pump4 = 5;
const int pump5 = 6;
const int pump6 = 7;

const float flowRate = 26.0; // mL/sec

void setup() {
  Serial.begin(9600);  // Bluetooth + USB serial
  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);
  pinMode(pump3, OUTPUT);
  pinMode(pump4, OUTPUT);
  pinMode(pump5, OUTPUT);
  pinMode(pump6, OUTPUT);

  // LOW-active relays: HIGH = OFF
  digitalWrite(pump1, HIGH);
  digitalWrite(pump2, HIGH);
  digitalWrite(pump3, HIGH);
  digitalWrite(pump4, HIGH);
  digitalWrite(pump5, HIGH);
  digitalWrite(pump6, HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.equalsIgnoreCase("clean")) {
      Serial.println("Starting cleaning mode...");
      cleanPumps();
      Serial.println("Cleaning complete!");
    }
    else if (command.startsWith("C_")) {
      command.remove(0, 2); // remove C_

      int pumpValues[6] = {0,0,0,0,0,0};
      int index = 0;

      while (command.length() > 0 && index < 6) {
        int underscoreIndex = command.indexOf('_');
        String value;

        if (underscoreIndex != -1) {
          value = command.substring(0, underscoreIndex);
          command = command.substring(underscoreIndex + 1);
        } else {
          value = command;
          command = "";
        }

        pumpValues[index] = value.toInt();
        index++;
      }

      // Run each pump sequentially
      for (int i = 0; i < 6; i++) {
        if (pumpValues[i] > 0) {
          dispensePump(i+1, pumpValues[i]);
        }
      }
      Serial.println("Dispense complete!");
    }
  }
}

// Run a specific pump for a calculated time
void dispensePump(int pumpNumber, int volume) {
  int pin = getPumpPin(pumpNumber);
  long duration = (volume / flowRate) * 1000;

  digitalWrite(pin, LOW);   // LOW = ON
  delay(duration);
  digitalWrite(pin, HIGH);  // HIGH = OFF
}

// Returns Arduino pin for pump number
int getPumpPin(int pumpNumber) {
  switch(pumpNumber) {
    case 1: return pump1;
    case 2: return pump2;
    case 3: return pump3;
    case 4: return pump4;
    case 5: return pump5;
    case 6: return pump6;
  }
  return 0;
}

// Cleaning mode: each pump ON 5s sequentially
void cleanPumps() {
  int pumpPins[6] = {pump1, pump2, pump3, pump4, pump5, pump6};
  for (int i = 0; i < 6; i++) {
    digitalWrite(pumpPins[i], LOW);
    delay(5000); // 5 seconds
    digitalWrite(pumpPins[i], HIGH);
  }
}




