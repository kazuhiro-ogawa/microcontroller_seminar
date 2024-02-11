#include <Arduino.h>
#include "Lcd.h"
#include <Wire.h>

// 初期化処理
void Lcd::init(){
  Wire.begin();
  init_LCD();
}

// 文字データ送信処理
void Lcd::writeData(byte t_data)
{
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(0x40);
  Wire.write(t_data);
  Wire.endTransmission();
  delay(1);
}

// コマンド送信処理
void Lcd::writeCommand(byte t_command)
{
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(0x00);
  Wire.write(t_command);
  Wire.endTransmission();
  delay(10);
}

// LCDの初期化処理
void Lcd::init_LCD() {
  delay(100);
  writeCommand(0x38);
  delay(20);
  writeCommand(0x39);
  delay(20);
  writeCommand(0x14);
  delay(20);
  writeCommand(0x73);
  delay(20);
  writeCommand(0x52);
  delay(20);
  writeCommand(0x6C);
  delay(20);
  writeCommand(0x38);
  delay(20);
  writeCommand(0x01);
  delay(20);
  writeCommand(0x0F);
  delay(20);
}

/*整数型変数などの数値を文字としてLCDに表示する関数*/
void Lcd::printNumber(int num){
  String temp = (String)num;
  int i  = 0;
  int len = temp.length();

  for(i = 0; i < len; i++){
    writeData(temp.charAt(i)); //CharAt()...引数で指定した位置の文字を返す
    delay(1);
  }
}

/*LCDのカーソルを自由に移動させる関数*/
void Lcd::cursorMove(int cursor_posi){     //返却値なし　引数　整数型(カーソルを移動させたいアドレス)
  writeCommand(0x80 + cursor_posi);   //インストラクションコード 0x80 カーソル移動
                                //それに移動させたいアドレスを足し合わせることで　そのアドレスにカーソルを移動させる
                                // writeCommand(place + 0x80);　が  プログラム中に出てきてもインストラクションコードを分からないと読めない
                                // cursorMoveなら名前から意味が想像しやすく　可読性　を上げることができる
}
