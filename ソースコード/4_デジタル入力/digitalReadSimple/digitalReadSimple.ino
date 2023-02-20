#define INPUT_PIN 4

void setup() {
  /* シリアルポートのデータ転送レートを9600bpsに設定 */
  Serial.begin(9600);

  /* 4番ピンをINPUTに設定 */
  pinMode(INPUT_PIN, INPUT);
}

void loop() {
  /* 4番ピンがHIGHだった時 */
  if(digitalRead(INPUT_PIN) == HIGH)
  {
    Serial.println("1");
  }
  else  /* 4番ピンがLOWだった時 */
  {
    Serial.println("0");
  }

  /* 100ミリ秒止める */
  delay(100);
}
