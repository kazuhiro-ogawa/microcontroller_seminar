#define LEDPIN 7
#define LEDLOOP 4
#define MSEC 1000

void setup() {
  // 7番ピンを出力に設定
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  
  // 7番ピンに0[V]出力
  digitalWrite(LEDPIN, LOW);
  
  // 1秒待つ
  delay(MSEC);

  for(int loop = 1; loop <= LEDLOOP; loop++)
  {
    // 7番ピンに5[V]出力
    digitalWrite(LEDPIN, HIGH);
    
    // 待つ
    delay(loop * MSEC);
    
    // 7番ピンに0[V]出力
    digitalWrite(LEDPIN, LOW);

    // 待つ
    delay(loop * MSEC);
  }
}
