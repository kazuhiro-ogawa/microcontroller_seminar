#include <Servo.h>

#define OPEN_SW_PIN 2
#define AFTER_SW_PIN 3
#define SERVO_PIN 9
#define LEDRED_PIN 7
#define ECHO 13 
#define TRIG 12

typedef enum{
  GATECLOSE,        // ゲート閉めて待機中
  GATEOPEN,         // ゲート開けて待機中
  CLOSED            // 営業時間外状態
}STATE;

typedef enum{
  ENTRY,
  DO,
  EXIT
}ACTION;

Servo servo;  // Servoクラスから インスタンスservoを生成
STATE g_state = GATECLOSE;
ACTION g_action = ENTRY;

void setAction(ACTION act){
  g_action = act;
}

ACTION getAction(){
  return g_action;
}

void setState(STATE state){
  g_state = state;
}

STATE getState(){
  return g_state;
}

void setStateAction(STATE state, ACTION action){
  setState(state);
  setAction(action);
}

double measureDistance(){
  double t; //ｔはμ秒単位
  double distance = -1;
  
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
  }
  return distance;
}

bool checkCar(){
  if(0.0 < measureDistance() && measureDistance() < 5.0){
    return true;
  }
  else{
    return false;
  }
}

void setup() {
  pinMode(LEDRED_PIN, OUTPUT);
  pinMode(OPEN_SW_PIN, INPUT_PULLUP);
  pinMode(AFTER_SW_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);

  //インスタンスがクラスの関数を使うには インスタンス名.クラスの関数名() 
  
  servo.attach(SERVO_PIN);  //サーボモータの使用ピン
  servo.write(0);           //サーボモータの角度を0度に設定
  delay(100);               //念のため100ms待つ
}

void loop() {

  static STATE tmpstate = GATECLOSE;

  switch(getState()){    
    case GATECLOSE:
      switch(getAction()){
        case ENTRY:
          setStateAction(GATECLOSE, DO);
          break;
        case DO:
          if(checkCar() || digitalRead(OPEN_SW_PIN) == LOW){
            tmpstate = GATEOPEN;
            setStateAction(GATECLOSE, EXIT);
          }
          else if(digitalRead(AFTER_SW_PIN) == LOW){
            tmpstate = CLOSED;
            setStateAction(GATECLOSE, EXIT);
          }

          break;
        case EXIT:
          setStateAction(tmpstate, ENTRY);
          break;
      }
      break;      
    case GATEOPEN:
      switch(getAction()){
        case ENTRY:
          // ゲートオープン
          servo.write(90);
          delay(5000);
          setStateAction(GATEOPEN, DO);
          break;
        case DO:
          setStateAction(GATEOPEN, EXIT);
          break;          
        case EXIT:
          // ゲートクローズ
          servo.write(0);
          setStateAction(GATECLOSE, ENTRY);
          break;
      }
      break;      
    case CLOSED:
      switch(getAction()){
        case ENTRY:
          delay(100);
          digitalWrite(LEDRED_PIN, HIGH);
          setStateAction(CLOSED, DO);
          break;
        case DO:
          if(digitalRead(AFTER_SW_PIN) == LOW){
            setStateAction(CLOSED, EXIT);
          }
          break;             
        case EXIT:
          digitalWrite(LEDRED_PIN, LOW);
          setStateAction(GATECLOSE, ENTRY);
          break;
      }
      break;
  }
  Serial.println(getState());
  Serial.println(getAction());
}
