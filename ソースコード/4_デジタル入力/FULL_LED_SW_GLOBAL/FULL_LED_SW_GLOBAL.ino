#define LED_RED 5
#define LED_BLUE 6
#define LED_GREEN 7
#define SW_PIN  4

typedef enum {
  RED,
  GREEN,
  BLUE,
}LED_COLOR;

LED_COLOR led_mode = RED;

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
    default:
      color_change(HIGH, LOW, LOW);
  }
}

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(SW_PIN, INPUT_PULLUP);
}

void loop() {

  if(digitalRead(SW_PIN) == LOW)
  {
    if(led_mode == RED){
      led_mode = GREEN;
    }
    else if(led_mode == GREEN){
      led_mode = BLUE;
    }
    else{
      led_mode = RED;
    }
  }

  color_set(led_mode);

  delay(100);
}


}
