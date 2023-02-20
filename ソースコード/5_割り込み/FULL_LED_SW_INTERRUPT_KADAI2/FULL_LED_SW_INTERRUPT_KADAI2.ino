#define LED_GREEN 7
#define INTERRUPT_PIN 0

volatile int led_mode = 0;

void mode_change(){
  led_mode++;
  if(led_mode > 3)
  {
    led_mode = 0;
  }
}

void led_blink(unsigned int blink_time){
  digitalWrite(LED_GREEN, HIGH);
  delay(blink_time);
  digitalWrite(LED_GREEN, LOW);
  delay(blink_time);
}

void led_mode_func(){
  switch(led_mode)
  {
    case 0: led_blink(0); break;
    case 1: led_blink(1000); break;
    case 2: led_blink(500); break;
    case 3: led_blink(100); break;
    default: led_blink(0);
  }
}

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  attachInterrupt(INTERRUPT_PIN, mode_change, FALLING);
}

void loop() {
    led_mode_func();
}
