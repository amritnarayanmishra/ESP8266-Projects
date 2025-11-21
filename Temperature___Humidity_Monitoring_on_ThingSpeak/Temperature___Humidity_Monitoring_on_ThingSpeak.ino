#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>

#define DHTPIN D4
#define DHTTYPE DHT11   // DHT22 bhi use kar sakte ho
DHT dht(DHTPIN, DHTTYPE);

// Wi-Fi Credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// ThingSpeak
const char* server = "http://api.thingspeak.com/update";
const String apiKey = "YOUR_THINGSPEAK_WRITE_API_KEY";

void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(temp) + "&field2=" + String(hum);
    
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("Data sent to ThingSpeak");
    } else {
      Serial.println("Error sending data");
    }
    http.end();
  }

  delay(15000); // ThingSpeak limit 15 sec
}
