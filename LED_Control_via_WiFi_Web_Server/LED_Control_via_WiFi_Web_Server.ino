#include <ESP8266WiFi.h>

const char* ssid = "ESP_LED";
const char* password = "12345678";

WiFiServer server(80);
int led = D5;

void setup() {
  pinMode(led, OUTPUT);
  WiFi.softAP(ssid, password);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\n');
  if (req.indexOf("/on") != -1) digitalWrite(led, HIGH);
  if (req.indexOf("/off") != -1) digitalWrite(led, LOW);

  client.print("LED: <a href=\"/on\">ON</a> | <a href=\"/off\">OFF</a>");
  delay(1);
}
