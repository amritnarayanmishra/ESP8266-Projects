#include <ESP8266WiFi.h>

int r1 = D6;
int r2 = D7;

WiFiServer server(80);

void setup() {
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);

  WiFi.begin("HomeAuto", "12345678");
  while (WiFi.status() != WL_CONNECTED) delay(300);
  server.begin();
}

void loop() {
  WiFiClient c = server.available();
  if (!c) return;

  String q = c.readStringUntil('\r');
  if (q.indexOf("/r1on")>0) digitalWrite(r1, HIGH);
  if (q.indexOf("/r1off")>0) digitalWrite(r1, LOW);
  if (q.indexOf("/r2on")>0) digitalWrite(r2, HIGH);
  if (q.indexOf("/r2off")>0) digitalWrite(r2, LOW);

  c.println("HTTP/1.1 200 OK");
  c.println("Content-Type: text/html\n");
  c.println("<h2>Home Automation</h2>");
  c.println("<a href='/r1on'>Relay1 ON</a> | <a href='/r1off'>OFF</a><br>");
  c.println("<a href='/r2on'>Relay2 ON</a> | <a href='/r2off'>OFF</a>");
}
