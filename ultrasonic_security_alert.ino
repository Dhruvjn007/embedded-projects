#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 8
#define ALERT_DISTANCE 15  // cm

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.println("Security system active...");
}

float getDistance() {
  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pulse duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Convert to cm: speed of sound = 343 m/s
  float distance = (duration * 0.0343) / 2;
  return distance;
}

void loop() {
  float dist = getDistance();

  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");

  if (dist > 0 && dist < ALERT_DISTANCE) {
    Serial.println("!!! SECURITY ALERT !!!");
    // Beep the buzzer
    tone(BUZZER_PIN, 1000, 500); // 1kHz tone for 500ms
  } else {
    noTone(BUZZER_PIN);
  }

  delay(300);
}
