#define VOL A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(VOL);
  Serial.println(val);
}
