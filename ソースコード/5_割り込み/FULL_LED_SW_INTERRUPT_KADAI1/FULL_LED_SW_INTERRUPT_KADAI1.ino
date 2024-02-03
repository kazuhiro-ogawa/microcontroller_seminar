#define LED_GREEN 7
#define INTERRUPT_PIN 0

typedef enum {
  NORMAL,
  BLINK_SLOW,
  BLINK_NORMAL,
  BLINK_FAST
}LEDMODE;

volatile LEDMODE led_mode = 0;

void mode_change(){
  Serial.println(led_mode);
  if(led_mode == NORMAL){
    led_mode = BLINK_SLOW;
  }
  else if(led_mode == BLINK_SLOW){
    led_mode = BLINK_NORMAL;
  }
  else if(led_mode == BLINK_NORMAL){
    led_mode = BLINK_FAST;
  }
  else{
    led_mode = NORMAL;
  }
}

void led_blink(int blink_time){
  digitalWrite(LED_GREEN, HIGH);
  delay(blink_time);
  digitalWrite(LED_GREEN, LOW);
  delay(blink_time);
}

void led_mode_func(LEDMODE mode){
  switch(mode)
  {
    case NORMAL: led_blink(0); break;
    case BLINK_SLOW: led_blink(1000); break;
    case BLINK_NORMAL: led_blink(500); break;
    case BLINK_FAST: led_blink(100); break;
    default: led_blink(0);
  }
}

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  attachInterrupt(INTERRUPT_PIN, mode_change, RISING);
  Serial.begin(9600);
}

void loop() {
    led_mode_func(led_mode);
}
