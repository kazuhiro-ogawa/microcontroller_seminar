#define LED_RED 5
#define LED_BLUE 6
#define LED_GREEN 7
#define COLOR_SW_PIN  4
#define BLINK_SW_PIN  3

int color_mode = 0;
int blink_mode = 0;

typedef enum {
  RED,
  GREEN,
  BLUE
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

  if(blink_mode == 0){
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
  }else{
    switch(color_num){
      case RED:
        color_change_blink(HIGH, LOW, LOW);
        break;
      case GREEN:
        color_change_blink(LOW, HIGH, LOW);
        break;
      case BLUE:
        color_change_blink(LOW, LOW, HIGH);
        break;
      default:
        color_change_blink(HIGH, LOW, LOW);
    }
  }
}

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(COLOR_SW_PIN, INPUT_PULLUP);
  pinMode(BLINK_SW_PIN, INPUT_PULLUP);
}

void loop() {

  if(digitalRead(COLOR_SW_PIN) == LOW)
  {
    color_mode++;
    if(color_mode > 2)
    {
      color_mode = 0;
    }
  }

  if(digitalRead(BLINK_SW_PIN) == LOW)
  {
    blink_mode++;
    if(blink_mode > 1)
    {
      blink_mode = 0;
    }
  }

  color_set(color_mode);

  delay(100);
}
