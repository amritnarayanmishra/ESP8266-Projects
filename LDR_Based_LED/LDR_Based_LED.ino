// LDR Reading with LED Control
int ldr = A0;
int led = D7;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  int v = analogRead(ldr);
  if (v < 500) digitalWrite(led, HIGH);
  else digitalWrite(led, LOW);
  delay(100);
}
