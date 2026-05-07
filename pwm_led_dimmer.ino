#define POT_PIN A0
#define LED_PIN 9

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potVal = analogRead(POT_PIN);       // 0 to 1023
  int brightness = map(potVal, 0, 1023, 0, 255); // scale to 0-255 for PWM

  analogWrite(LED_PIN, brightness);

  Serial.print("Pot: ");
  Serial.print(potVal);
  Serial.print("  Brightness: ");
  Serial.println(brightness);

  delay(50);
}
