#define LED_RED 5
#define LED_BLUE 6
#define LED_GREEN 7
#define TRIG_PIN 12
#define ECHO_PIN 13

typedef enum {
  RED,
  GREEN,
  BLUE,
  WHITE
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
    case WHITE:
      color_change(HIGH, HIGH, HIGH);
      break;
  }
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  double duration = pulseIn(ECHO_PIN, HIGH);
  double distance = (340.0 / 1000000.0) * (duration / 2);
  double d = distance * 100;

  if(0 <= d && d < 5){
    color_set(RED);
  }else if(5 <= d && d < 10){
    color_set(GREEN);
  }else if(10 <= d && d < 20){
    color_set(BLUE);
  }else if(20 <= d){
    color_set(WHITE);
  }

  Serial.print(d);
  Serial.println("[cm]");
  delay(500);  
}
