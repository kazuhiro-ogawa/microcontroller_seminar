#include <MsTimer2.h>

#define LED_GREEN 7
#define SW_PIN_INTERRUPT 0
#define TIMETIME 1000

typedef enum{
  OFF,
  ON
}LEDSTATE;

volatile LEDSTATE led_state = OFF;

void led_change()
{
  if(led_state == OFF)
  {
    led_state = ON;
  }
  else{
    led_state = OFF;
  }
  if(led_state == ON)
  {
    digitalWrite(LED_GREEN, HIGH);
  }
  else
  {
    digitalWrite(LED_GREEN, LOW);
  }
  MsTimer2::stop();
}

void timer_start()
{
  MsTimer2::start();
}

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  MsTimer2::set(TIMETIME, led_change);
  attachInterrupt(SW_PIN_INTERRUPT, timer_start, RISING);
}

void loop() {

}
