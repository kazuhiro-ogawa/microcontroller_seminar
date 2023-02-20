#define GREEN_PIN 7
#define BLUE_PIN 6
#define RED_PIN 5
#define LED_WAIT 2000

void setup() {
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
}

void loop() {
  // put on RED
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
  delay(LED_WAIT);

  // put on GREEN
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
  delay(LED_WAIT);

  // put on BLUE
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
  digitalWrite(RED_PIN, LOW);
  delay(LED_WAIT);

  // put on YELLOW
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
  delay(LED_WAIT);

  // put on SKYBLUE
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
  digitalWrite(RED_PIN, LOW);
  delay(LED_WAIT);

  // put on PURPLE
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
  digitalWrite(RED_PIN, HIGH);
  delay(LED_WAIT);
}
