#define LED_RED 5
#define LED_BLUE 6
#define LED_GREEN 7
#define INTERRUPT_PIN 0

volatile int led_mode = 0;

typedef enum {
  RED,
  GREEN,
  BLUE
}LED_COLOR;

void mode_change()
{
  led_mode++;
  Serial.println(led_mode);
  if(led_mode > 2)
  {
    led_mode = 0;
  }
}

void color_change(bool red, bool green, bool blue)
{
  digitalWrite(LED_RED, red);
  digitalWrite(LED_GREEN, green);
  digitalWrite(LED_BLUE, blue);
}

void color_set(){
  switch(led_mode){
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
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  attachInterrupt(INTERRUPT_PIN, mode_change, FALLING);
}

void loop() {
  color_set();
}
