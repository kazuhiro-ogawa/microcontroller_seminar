#include "LCD.h"

Lcd lcd;

void setup() {
  lcd.init();
}

void loop() {
  static int cnt = 0;

  if(cnt >= 15){
    cnt = 0;
    lcd.writeCommand(0x01);
  }
  
  lcd.cursorMove(0x40);
  lcd.printNumber(cnt);
  
  cnt++;
  delay(1000);
}
 
