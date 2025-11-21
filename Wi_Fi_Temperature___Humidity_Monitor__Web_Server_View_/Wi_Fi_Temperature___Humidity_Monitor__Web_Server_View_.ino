#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.begin("ESP8266", "12345678");
  while (WiFi.status() != WL_CONNECTED) delay(300);
  server.begin();
}

void loop() {
  WiFiClient c = server.available();
  if (!c) return;

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  c.readStringUntil('\r');

  c.println("HTTP/1.1 200 OK");
  c.println("Content-Type: text/html\n");
  c.print("Temp: "); c.print(t);
  c.print(" C  Humidity: "); c.print(h);
}
