#include <uTimerLib.h>
#define LED_RED 7
#define LED_BLUE 6
#define LED_GREEN 5

volatile int color_no = 0;

void color_change(bool red, bool green, bool blue)
{
  digitalWrite(LED_RED, red);
  digitalWrite(LED_GREEN, green);
  digitalWrite(LED_BLUE, blue);
}

void timerTask()
{
  switch(color_no)
  {
    case 0: color_change(HIGH, LOW, LOW); break; // red
    case 1: color_change(LOW, HIGH, LOW); break; // green
    case 2: color_change(LOW, LOW, HIGH); break; // blue
    case 3: color_change(HIGH, HIGH, LOW); break;  // yellow
    case 4: color_change(LOW, HIGH, HIGH); break; // sky blue
    case 5: color_change(HIGH, LOW, HIGH); break; // purple
  }
  color_no++;
  if(color_no > 5)
  {
    color_no = 0;
  }
}

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  TimerLib.setInterval_s(timerTask, 2);
}

void loop() {

}
