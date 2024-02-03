#define ECHO 13 
#define TRIG 12

void setup() {
  pinMode(ECHO,INPUT);
  pinMode(TRIG,OUTPUT);
  Serial.begin(9600);
}
  
void loop() {

  double t; //ｔはμ秒単位
  double distance;
  
  /*超音波の発生*/
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);

  /*返ってくるまでの時間測定*/
  t = pulseIn(ECHO,HIGH); //ECHOピンのパルスがHIGHになった時間を変数tに格納
  if(t >= 0){
    distance = (340.0/1000000) * t * 0.5 * 100;//m→cmなので100倍する
    Serial.print(distance);
    Serial.println("[cm]");
    delay(300);
  }
}
