// Bluetooth RC Car - 4 Motors - Arduino UNO R4 WiFi
// Uses built-in Bluetooth on UNO R4 WiFi
// Compatible with common RC car apps (e.g., "Bluetooth RC Controller" on Play Store)
//
// Motor Driver: L298N (x2, one per side) or L298N dual bridge
// Motor wiring (left side):
//   IN1 -> 4, IN2 -> 5, ENA -> 6  (left motors)
// Motor wiring (right side):
//   IN3 -> 7, IN4 -> 8, ENB -> 9  (right motors)
//
// Most RC apps send single characters:
//   'F' = forward, 'B' = backward, 'L' = left, 'R' = right, 'S' = stop
// Some apps send 'G','H','I','J' for diagonal - we'll handle basics here.

#include <ArduinoBLE.h>

// Left motors
#define IN1 4
#define IN2 5
#define ENA 6

// Right motors
#define IN3 7
#define IN4 8
#define ENB 9

#define SPEED 180  // 0-255, adjust as needed

// BLE service for Serial-like communication
BLEService rcService("FFE0");
BLEStringCharacteristic rcChar("FFE1", BLERead | BLEWrite | BLENotify, 20);

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void turnLeft() {
  // Left wheels backward, right wheels forward
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void turnRight() {
  // Left wheels forward, right wheels backward
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void handleCommand(char cmd) {
  Serial.print("Command: ");
  Serial.println(cmd);

  switch (cmd) {
    case 'F': moveForward(); break;
    case 'B': moveBackward(); break;
    case 'L': turnLeft(); break;
    case 'R': turnRight(); break;
    case 'S': stopMotors(); break;
    default: break;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(ENB, OUTPUT);
  stopMotors();

  if (!BLE.begin()) {
    Serial.println("BLE init failed!");
    while (1);
  }

  BLE.setLocalName("DhruvRC-Car");
  BLE.setAdvertisedService(rcService);
  rcService.addCharacteristic(rcChar);
  BLE.addService(rcService);
  BLE.advertise();

  Serial.println("RC Car BLE ready. Connect via app.");
  Serial.println("Device name: DhruvRC-Car");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected: ");
    Serial.println(central.address());

    while (central.connected()) {
      if (rcChar.written()) {
        String val = rcChar.value();
        if (val.length() > 0) {
          handleCommand(val[0]);
        }
      }
    }

    stopMotors();
    Serial.println("Disconnected. Stopping motors.");
  }
}

/*
  NOTES:
  - Install "ArduinoBLE" library from Library Manager
  - App recommendation: "Arduino Bluetooth RC Car" or "BLE RC Controller" from Play Store
  - Make sure to pair your phone with "DhruvRC-Car" in Bluetooth settings first
  - If using an app that sends different characters, update the switch-case above
  - You can also adjust SPEED per direction for better turning control
*/
