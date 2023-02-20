#include <EEPROM.h>
#define LED_RED 5
#define LED_BLUE 6
#define LED_GREEN 7
#define LED_STATE_ADDRESS 0

typedef enum {
  RED,
  GREEN,
  BLUE,
  YELLOW,
  SKYBLUE,
  PURPLE
}LED_COLOR;

void color_change(bool red, bool green, bool blue)
{
  digitalWrite(LED_RED, red);
  digitalWrite(LED_GREEN, green);
  digitalWrite(LED_BLUE, blue);
}

void color_set(LED_COLOR color_num){
  switch(color_num){
    case RED:
      color_change(HIGH, LOW, LOW);
      break;
    case GREEN:
      color_change(LOW, HIGH, LOW);
      break;
    case BLUE:
      color_change(LOW, LOW, HIGH);
      break;
    case YELLOW:
      color_change(HIGH, HIGH, LOW);
      break;
    case SKYBLUE:
      color_change(LOW, HIGH, HIGH);
      break;
    case PURPLE:
      color_change(HIGH, LOW, HIGH);
      break;
    default:
      color_change(HIGH, LOW, LOW);
  }
  write_ledmode((byte)color_num);
}

int read_ledmode(){
  int value = EEPROM.read(LED_STATE_ADDRESS);
  Serial.print("アドレス0x00 : 0x");
  Serial.println(value, HEX);
  return value;
}

void write_ledmode(byte ledmode){
  EEPROM.write(LED_STATE_ADDRESS, ledmode);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  color_set((byte)read_ledmode());
}

void loop() {
  int value;
  byte input = 0;
  bool break_flg = false;

  Serial.println("");
  Serial.println("----- MENU -----");
  Serial.println("1.Set Color RED");
  Serial.println("2.Set Color GREEN");
  Serial.println("3.Set Color BLUE");
  Serial.println("4.Set Color YELLOW");
  Serial.println("5.Set Color SKYBLUE");
  Serial.println("6.Set Color PURPLE");
  Serial.println("");

  while(1){
    if(Serial.available()>0){  // 入力された文字が何バイトか調べその回数分繰り返す
      input = Serial.read() - 48;   // 1バイト分のデータを読み取る

      switch(input){
        case RED:
        case GREEN:     
        case BLUE:
        case YELLOW:
        case SKYBLUE:
        case PURPLE:
          color_set(input);
          break_flg = true;
          break;
      }
    }
    if(break_flg == true)
    {
      break_flg = false;
      break;
    }
  }
  
}
