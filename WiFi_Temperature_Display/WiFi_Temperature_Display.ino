#include <ESP8266WiFi.h>
#include <DHT.h>

DHT dht(D4, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.print("T: "); Serial.print(t);
  Serial.print(" C | H: "); Serial.println(h);
  delay(2000);
}
