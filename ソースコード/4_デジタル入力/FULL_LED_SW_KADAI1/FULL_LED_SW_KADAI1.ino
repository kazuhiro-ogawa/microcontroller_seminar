#define LED_RED 5
#define LED_BLUE 6
#define LED_GREEN 7
#define SW_PIN  4

int led_mode = 0;

typedef enum {
  RED,
  GREEN,
  BLUE,
  RED_BLINK,
  GREEN_BLINK,
  BLUE_BLINK
}LED_COLOR;

void color_change(bool red, bool green, bool blue)
{
  digitalWrite(LED_RED, red);
  digitalWrite(LED_GREEN, green);
  digitalWrite(LED_BLUE, blue);
}

void color_change_blink(bool red, bool green, bool blue)
{
  digitalWrite(LED_RED, red);
  digitalWrite(LED_GREEN, green);
  digitalWrite(LED_BLUE, blue);
  delay(100);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  delay(100);
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
    case RED_BLINK:
      color_change_blink(HIGH, LOW, LOW);
      break;
    case GREEN_BLINK:
      color_change_blink(LOW, HIGH, LOW);
      break;
    case BLUE_BLINK:
      color_change_blink(LOW, LOW, HIGH);
      break;
    default:
      color_change(HIGH, LOW, LOW);
  }
}

void setup() {
  // 7番ピンを出力に設定
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(SW_PIN, INPUT_PULLUP);
}

void loop() {

  if(digitalRead(SW_PIN) == LOW)
  {
    led_mode++;
    if(led_mode > 5)
    {
      led_mode = 0;
    }
  }

  color_set(led_mode);

  delay(100);
}
