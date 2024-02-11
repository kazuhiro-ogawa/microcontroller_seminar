#include <Wire.h>                   // Wire.h　→　I2Cのデバイスを制御するための関数ライブラリ
#define LCD_ADRS 0x3E               // LCDのスレーブ(フォロワー)アドレス
char moji[] ="AQM1602XA-RN-GBW";    // LCDに表示する文字列
                                    // SCL=A5=LCDNo2 SDA=A4=LCDNo3

void setup() {
  Wire.begin();                     // Wire.hの関数を使用する下準備(Wireライブラリの初期化)
  init_LCD();                       // LCDの初期化を行う関数(自作)
}

void loop() {
  
  cursorMove(0x09);
  int num = 573;
  printNumber(num);
  writeCommand(0x0F);
  while(1){}//stop
} 


// データ書き込み
void writeData(byte t_data)         // 返却値無し、引数 byte型 (1byteの整数) 機能　引数のデータをLCDに表示させる(書き込む)
{
  Wire.beginTransmission(LCD_ADRS); // I2Cの通信を開始     ①スレーブアドレスの送信
  Wire.write(0x40);                 // 0x40の書き込み      ②コントロールバイトの送信　0x40　→ 0100 0000   RS = 1(次のデータは表示データ)
  Wire.write(t_data);               // データの書き込み     ③データの送信(1文字分のデータがLCDに表示される)
  Wire.endTransmission();           // 通信の終了
  delay(1);
}

//コマンド書き込み
void writeCommand(byte t_command)   // 返却値無し　引数　byte型(1byte整数を格納する型) 
{
  Wire.beginTransmission(LCD_ADRS);  // I2Cの通信を LCD_ADRSのデバイスと 開始       ①スレーブアドレスの送信
  Wire.write(0x00);                  // 通信先デバイスに 0ｘ00(0000 0000)を送信     ②コントロールバイトの送信　RS=0(次のデータはインストラクションコード)
  Wire.write(t_command);             // 引数のデータを通信先デバイスに送信            ③データの送信(インストラクションコードの送信)
  Wire.endTransmission();            // I2Cの通信の終了(データを送り終わったら必ず行う)
  delay(10);
}

void init_LCD() {                   // initialize_LCDの略 引数無し　返却値無し LCDの初期化を行う
  delay(100);
  writeCommand(0x38);               // writeCommand関数　→　LCDインストラクションコードを送る関数(自作)
                                    // 0x38　→  8ビットデータ通信　2行表示　1行1文字表示 命令表0を使用する (LCDの初期設定) 
  delay(20);                        // インストラクションコードは実行に時間がかかるため、いくらかの待ち時間が必要(待ち時間はデータシート参照)
  writeCommand(0x39);               // ここから下は拡張コマンド LCDのデータシートに載っていない
  delay(20);
  writeCommand(0x14);
  delay(20);
  writeCommand(0x73);
  delay(20);
  writeCommand(0x52);
  delay(20);
  writeCommand(0x6C);
  delay(20);
  writeCommand(0x38);               // ここまで拡張コマンド
  delay(20);
  writeCommand(0x01);
  delay(20);
  writeCommand(0x0C);
  delay(20);
}

void cursorMove(int cursor_posi){
  writeCommand(0x80 + cursor_posi);
}

void printNumber(int num){
  String str = String(num);
  int len = str.length();

  for(int i = 0; i < len; i++){
    writeData(str.charAt(i));
    delay(1);
  }
}
