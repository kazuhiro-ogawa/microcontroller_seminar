#define LEDPIN 7
#define DELAY_TIME 1000
#define DELAY_BLINK 250

void setup() {
  // 7番ピンを出力に設定
  pinMode(LEDPIN, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {

  int led_count = 0;  // 点滅回数用変数
  int loop = 0;       // forループ用変数
  
  // 7番ピンに0[V]出力
  digitalWrite(LEDPIN, LOW);
  
  // 1秒待つ
  delay(DELAY_TIME);

  // 点滅回数を取得
  led_count = random(1,6);

  for(loop = 0; loop < led_count; loop++)
  {
    // 7番ピンに5[V]出力
    digitalWrite(LEDPIN, HIGH);
    
    // 0.25秒待つ
    delay(DELAY_BLINK);
    
    // 7番ピンに0[V]出力
    digitalWrite(LEDPIN, LOW);

    // 0.25秒待つ
    delay(DELAY_BLINK);
  }
}
