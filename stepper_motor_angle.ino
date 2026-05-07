#include <Stepper.h>

#define STEPS_PER_REV 2048  // 28BYJ-48 has 2048 steps per full revolution
#define POT_PIN A0

// Note: pin order matters for 28BYJ-48 with Stepper library
Stepper stepper(STEPS_PER_REV, 8, 10, 9, 11);

int currentAngle = 0;

void setup() {
  stepper.setSpeed(10); // RPM - keep it low for 28BYJ-48
  Serial.begin(9600);
  Serial.println("Stepper Motor Angle Control");
  Serial.println("Turn pot to change angle (0-360 degrees)");
}

void loop() {
  int potVal = analogRead(POT_PIN);
  int targetAngle = map(potVal, 0, 1023, 0, 360);

  int diff = targetAngle - currentAngle;

  // Only move if the angle changed by more than 2 degrees (avoid jitter)
  if (abs(diff) > 2) {
    int stepsToMove = map(diff, -360, 360, -STEPS_PER_REV, STEPS_PER_REV);
    stepper.step(stepsToMove);
    currentAngle = targetAngle;

    Serial.print("Moving to angle: ");
    Serial.print(targetAngle);
    Serial.println("°");
  }

  delay(100);
}
