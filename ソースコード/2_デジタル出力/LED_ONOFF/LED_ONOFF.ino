#define LEDPIN 7
#define DELAY_LED 2000

void setup() {
  // 7番ピンを出力に設定
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  digitalWrite(LEDPIN, HIGH);
  delay(DELAY_LED);
  digitalWrite(LEDPIN, LOW);
  delay(DELAY_LED); 
}
