#include <MsTimer2.h>

#define LEDPIN 7
#define SW_PIN_INTERRUPT 0
volatile int flg = 1;

void led_change()
{
  if(flg == 0)
  {
    flg = 1;
  }
  else{
    flg = 0;
  }

  Serial.println(flg);
  
  if(flg == 1)
  {
    digitalWrite(LEDPIN, HIGH);
  }
  else
  {
    digitalWrite(LEDPIN, LOW);
  }
  MsTimer2::stop();
}

void timer_restart()
{
  digitalWrite(LEDPIN, HIGH);
  flg = 1;
  MsTimer2::stop();
  MsTimer2::start();
}

void setup() {
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);
  MsTimer2::set(5000, led_change);
  attachInterrupt(SW_PIN_INTERRUPT, timer_restart, RISING);
  MsTimer2::start();
}

void loop() {

}
