#define VOL A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(VOL);
  float volt = 5.0 * val / 1024;
  Serial.println(volt);
}
