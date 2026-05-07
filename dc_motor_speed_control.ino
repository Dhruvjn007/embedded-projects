#define POT_PIN A0
#define IN1 7
#define IN2 8
#define ENA 9

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Set direction: forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  Serial.begin(9600);
  Serial.println("DC Motor Speed Control Ready");
}

void loop() {
  int potVal = analogRead(POT_PIN);
  int speed = map(potVal, 0, 1023, 0, 255);

  analogWrite(ENA, speed);

  Serial.print("Pot: ");
  Serial.print(potVal);
  Serial.print("  Motor Speed: ");
  Serial.println(speed);

  delay(100);
}
