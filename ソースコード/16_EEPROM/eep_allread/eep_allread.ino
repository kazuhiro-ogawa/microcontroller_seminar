#include <EEPROM.h>

void read_all(){

  Serial.println("         00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
  for(int addless = 0; addless < 1024; addless += 0x10){
    char sendPacket[8] = "";
    sprintf(sendPacket, "%03x", addless);
   
    Serial.print("0x");
    Serial.print(sendPacket);
    Serial.print(" : ");
    for(int add = 0; add < 0x10; add++){
      int value = EEPROM.read(addless + add);
      Serial.print(" ");
      char sendPacket2[8] = "";
      sprintf(sendPacket2, "%02X", value);
      Serial.print(sendPacket2);
    }
    Serial.println("");
  }
}

void setup() {
    Serial.begin(115200);
}

void loop() {

  read_all();
  
  while(1){
  };
}
