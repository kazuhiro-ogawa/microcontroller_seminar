#define LED_RED 5
#define LED_BLUE 6
#define LED_GREEN 7
#define VOL A0

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
  Serial.begin(9600);
}

void loop() {
  double volt = analogRead(VOL)*((double)5/1024);
  Serial.println(volt);
  
  if(volt >= 3.0){
    color_change(HIGH,HIGH,HIGH);
  }
  else if(volt >= 2.0){
    color_change(LOW,HIGH,LOW);
  }
  else if(volt >= 1.0){
    color_change(LOW,LOW,HIGH);
  }
  else if(volt >= 0.0){
    color_change(HIGH,LOW,LOW);
  }

}
