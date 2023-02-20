#define LED_RED 5
#define LED_BLUE 6
#define LED_GREEN 7

typedef enum {
  RED,
  GREEN,
  BLUE,
  YELLOW,
  SKYBLUE,
  PURPLE
}LED_COLOR;

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

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

void loop() {

  // red
  color_set(RED);
  delay(2000);

  // green
  color_set(GREEN);
  delay(2000);

  // blue
  color_set(BLUE);
  delay(2000);

  // yellow
  color_set(YELLOW);
  delay(2000);

  // sky blue
  color_set(SKYBLUE);
  delay(2000);

  // purple
  color_set(PURPLE);
  delay(2000);
}
