#include <DHT.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("DHT11 Sensor Ready");
  Serial.println("-------------------");
}

void loop() {
  delay(2000); // DHT11 needs at least 2s between reads

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature(); // Celsius by default

  // Check if reading failed
  if (isnan(humidity) || isnan(temp)) {
    Serial.println("Failed to read from DHT11!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C  |  Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}
