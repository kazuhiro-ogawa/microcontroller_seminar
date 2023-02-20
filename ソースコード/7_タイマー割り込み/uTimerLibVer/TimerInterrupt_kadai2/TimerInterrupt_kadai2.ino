#include <uTimerLib.h>

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
}

void timer_restart()
{
  digitalWrite(LEDPIN, HIGH);
  flg = 1;
  TimerLib.clearTimer();
  TimerLib.setTimeout_s(led_change, 5);
}

void setup() {
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);
  attachInterrupt(SW_PIN_INTERRUPT, timer_restart, RISING);
  TimerLib.setTimeout_s(led_change, 5);
}

void loop() {

}
