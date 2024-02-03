#define LED_RED 5
#define LED_BLUE 6
#define LED_GREEN 7

void color_change(bool red, bool green, bool blue)
{
  digitalWrite(LED_RED, red);
  digitalWrite(LED_GREEN, green);
  digitalWrite(LED_BLUE, blue);
}

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

void loop() {

  // red
  color_change(HIGH, LOW, LOW);
  delay(2000);

  // green
  color_change(LOW, HIGH, LOW);
  delay(2000);

  // blue
  color_change(LOW, LOW, HIGH);
  delay(2000);

  // yellow
  color_change(HIGH, HIGH, LOW);
  delay(2000);

  // sky blue
  color_change(LOW, HIGH, HIGH);
  delay(2000);

  // purple
  color_change(HIGH, LOW, HIGH);
  delay(2000);
}
