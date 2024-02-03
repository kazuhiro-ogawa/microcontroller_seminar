#include <MsTimer2.h>

#define LED_GREEN 7
#define SW_PIN_INTERRUPT 0
#define TIMERTIME 5000

typedef enum{
  OFF,
  ON
}LEDSTATE;

volatile LEDSTATE led_state = ON;

void led_change()
{
  if(led_state == OFF)
  {
    led_state = ON;
  }
  else{
    led_state = OFF;
  }

  Serial.println("led_state = " + led_state);
  
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

void timer_restart()
{
  digitalWrite(LED_GREEN, HIGH);
  led_state = ON;
  MsTimer2::stop();
  MsTimer2::start();
}

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, HIGH);
  MsTimer2::set(TIMERTIME, led_change);
  attachInterrupt(SW_PIN_INTERRUPT, timer_restart, RISING);
  MsTimer2::start();
}

void loop() {

}
