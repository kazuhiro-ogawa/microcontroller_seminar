void setup() {
  Serial.begin(9600);
}

void loop() {

  int incomingByte = 0;  // 受信データ用
  
  if(Serial.available() > 0) { // 受信したデータが存在する
    incomingByte = Serial.read(); // 受信データを読み込む

    Serial.print("I received: 0x"); // 受信データを送りかえす
    Serial.println(incomingByte, HEX);  // 16進数で表示
  }

}
