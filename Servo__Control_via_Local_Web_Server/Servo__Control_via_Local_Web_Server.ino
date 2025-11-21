#include <ESP8266WiFi.h>
#include <Servo.h>

const char* ssid = "ESP_Server";
const char* password = "12345678";

Servo myServo;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  myServo.attach(D4); // Servo pin
  myServo.write(90);  // initial position

  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\r');
  client.flush();

  if (req.indexOf("/pos0") != -1) myServo.write(0);
  if (req.indexOf("/pos45") != -1) myServo.write(45);
  if (req.indexOf("/pos90") != -1) myServo.write(90);
  if (req.indexOf("/pos135") != -1) myServo.write(135);
  if (req.indexOf("/pos180") != -1) myServo.write(180);

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  
  client.println("<!DOCTYPE html>");
  client.println("<html lang='en'>");
  client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1'>");
  client.println("<title>Servo Control</title>");
  client.println("<style>");
  
  // BODY STYLE
  client.println("body{font-family: 'Segoe UI', Tahoma, sans-serif; text-align:center; background: linear-gradient(135deg, #fceabb, #f8b500); margin:0; padding:50px;}");

  // TITLE STYLE
  client.println("h2{color:#ff0066; text-shadow: 2px 2px #fff;}");

  // BUTTON STYLE
  client.println(".btn{display:inline-block;padding:20px 35px;margin:15px;font-size:20px;font-weight:bold;cursor:pointer;");
  client.println("border:none; border-radius:15px; color:white; background: linear-gradient(45deg,#ff6a00,#ee0979);");
  client.println("box-shadow: 0 5px 15px rgba(0,0,0,0.3); transition:0.3s;}");

  // HOVER EFFECT
  client.println(".btn:hover{background: linear-gradient(45deg,#56ab2f,#a8e063); transform:scale(1.1); box-shadow: 0 8px 20px rgba(0,0,0,0.4);}"); 

  // RESPONSIVE
  client.println("@media(max-width:600px){.btn{padding:15px 25px; font-size:18px; margin:10px;}}");

  client.println("</style></head>");
  
  client.println("<body>");
  client.println("<h2>ESP8266 Servo Control 🌈</h2>");
  client.println("<a href='/pos0'><button class='btn'>0°</button></a>");
  client.println("<a href='/pos45'><button class='btn'>45°</button></a>");
  client.println("<a href='/pos90'><button class='btn'>90°</button></a>");
  client.println("<a href='/pos135'><button class='btn'>135°</button></a>");
  client.println("<a href='/pos180'><button class='btn'>180°</button></a>");
  client.println("</body></html>");
}
