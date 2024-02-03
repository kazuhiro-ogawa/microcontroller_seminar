#include <MsTimer2.h>
#define LED_RED 5
#define LED_BLUE 6
#define LED_GREEN 7
#define TIMERTIME 2000

typedef enum {
  RED,
  GREEN,
  BLUE,
  YELLOW,
  SKYBLUE,
  PURPLE
}LED_COLOR;

volatile LED_COLOR led_mode = RED;

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
}

void timerTask()
{
  switch(led_mode){
    case RED: led_mode = GREEN; break;
    case GREEN: led_mode = BLUE; break;
    case BLUE: led_mode = YELLOW; break;
    case YELLOW: led_mode = SKYBLUE; break;
    case SKYBLUE: led_mode = PURPLE; break;
    case PURPLE: led_mode = RED; break;
    default: led_mode = RED;
  }
}

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  MsTimer2::set(TIMERTIME, timerTask);
  MsTimer2::start();
}

void loop() {
  color_set(led_mode);
}
