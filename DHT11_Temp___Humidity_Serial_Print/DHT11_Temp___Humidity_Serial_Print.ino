#include <DHT.h>

#define DHTPIN D3
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("T: "); Serial.print(t);
  Serial.print(" C  H: "); Serial.println(h);

  delay(2000);
}
