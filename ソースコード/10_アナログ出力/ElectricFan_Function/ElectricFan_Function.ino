/*タクトスイッチのPIN D2を使うので0*/
#define PIN_SW 0
                          
/*モータ制御用のPIN*/
#define PIN_IN1  8
#define PIN_IN2  7
#define PIN_VREF 9 // PWM

typedef enum{
  STOP,
  WEAK,
  NORMAL,
  STRONG
}STATE;

typedef enum{
  ENTRY,
  DO,
  EXIT
}ACTION;

volatile STATE g_state = STOP;
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

void changeMode(){
  setAction(EXIT);
}

void motorControl(bool in1, bool in2){
  digitalWrite(PIN_IN1, in1);
  digitalWrite(PIN_IN2, in2);
}

void motorSpeed(int motor_speed){
  if(motor_speed < 0 && motor_speed > 255){
    motor_speed = 0;
  }
  analogWrite(PIN_VREF, motor_speed); 
}

void setup(){
  attachInterrupt(PIN_SW, changeMode, FALLING);       /* SWはD2で割り込み */

  pinMode(PIN_IN1,OUTPUT);      /* 回転方向制御 */
  pinMode(PIN_IN2,OUTPUT);      /* 回転方向制御 */
  pinMode(PIN_VREF,OUTPUT);     /* 回転速度制御 */
  
  motorSpeed(0);                /* モーターの回転速度を0にする(急に動き出さないように) */
  motorControl(LOW, LOW);       /* モーターを停止する */

  Serial.begin(9600);
}
 
void loop(){
  
    //Serial.println(fanMode);

    switch(getState()){
      case STOP:
        switch(getAction()){
          case ENTRY:
            /* 停止モード */
            motorControl(LOW, LOW); /* モーターを停止する */
            motorSpeed(0);
            setStateAction(STOP, DO);
            break;
          case DO:
            break;
          case EXIT:
            setStateAction(WEAK, ENTRY);
            break;
        }
        break;
      case WEAK:
        switch(getAction()){
          case ENTRY:
            /* 弱モード */
            motorControl(LOW, HIGH); /* モーターを反転する */
            motorSpeed(90);
            setStateAction(WEAK, DO);
            break;
          case DO:
            break;
          case EXIT:
            setStateAction(NORMAL, ENTRY);
            break;
        }
        break;     
      case NORMAL:
        switch(getAction()){
          case ENTRY:
            /* 中モード */
            motorControl(LOW, HIGH); /* モーターを反転する */
            motorSpeed(150);
            setStateAction(NORMAL, DO);
            break;
          case DO:
            break;
          case EXIT:
            setStateAction(STRONG, ENTRY);
            break;
        }
        break;     
      case STRONG:
        switch(getAction()){
          case ENTRY:
            /* 強モード */
            motorControl(LOW, HIGH); /* モーターを反転する */
            motorSpeed(220);
            setStateAction(STRONG, DO);
            break;
          case DO:
            break;
          case EXIT:
            setStateAction(STOP, ENTRY);
            break;
        }
        break;     
    }
}
