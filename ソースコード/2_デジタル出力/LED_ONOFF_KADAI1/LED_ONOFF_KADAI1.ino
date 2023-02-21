#define LEDPIN 7
#define DELAY_LED 3000
int led_count = 0;  // 点滅回数用変数

void setup() {
  // 7番ピンを出力に設定
  pinMode(LEDPIN, OUTPUT);
}

void loop() {

  /* led_countが2になったらif文に入らなくなる
     つまり、led_countが0,1の時にif文の中に入る */
  if(led_count < 2)
  {
    // 7番ピンに5[V]出力
    digitalWrite(LEDPIN, HIGH);
    
    // 3秒待つ
    delay(DELAY_LED);
  
    // 7番ピンに0[V]出力
    digitalWrite(LEDPIN, LOW);
  
    // 3秒待つ
    delay(DELAY_LED);

    // led_countをインクリメントする
    led_count++;
  }

}
