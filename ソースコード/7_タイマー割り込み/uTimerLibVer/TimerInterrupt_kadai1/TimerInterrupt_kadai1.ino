#include <uTimerLib.h>

#define LEDPIN 7
#define SW_PIN_INTERRUPT 0

void led_change()
{
  volatile static int flg = 0;
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
}

void timer_start()
{
  TimerLib.setTimeout_s(led_change, 1);
}

void setup() {
  pinMode(LEDPIN, OUTPUT);
  attachInterrupt(SW_PIN_INTERRUPT, timer_start, RISING);
}

void loop() {

}
