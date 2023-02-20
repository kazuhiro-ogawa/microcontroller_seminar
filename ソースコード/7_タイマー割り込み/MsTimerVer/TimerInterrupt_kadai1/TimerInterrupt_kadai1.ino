#include <MsTimer2.h>

#define LEDPIN 7
#define SW_PIN_INTERRUPT 0

volatile int flg = 0;

void led_change()
{
  
  if(flg == 0)
  {
    flg = 1;
  }
  else{
    flg = 0;
  }
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

void timer_start()
{
  MsTimer2::start();
}

void setup() {
  pinMode(LEDPIN, OUTPUT);
  MsTimer2::set(1000, led_change);
  attachInterrupt(SW_PIN_INTERRUPT, timer_start, RISING);
}

void loop() {

}
