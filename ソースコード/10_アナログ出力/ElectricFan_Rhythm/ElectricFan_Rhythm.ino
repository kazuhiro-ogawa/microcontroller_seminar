/*タクトスイッチのPIN D2を使うので0*/
#define PIN_SW 0
                          
/*モータ制御用のPIN*/
#define PIN_IN1 8
#define PIN_IN2 7
#define PIN_VREF 9 // PWM
#define WEAK_RSL 3
#define NORMAL_RSL 5
#define STRONG_RSL 7

typedef enum{
  STOP,
  WEAK,
  NORMAL,
  STRONG,
  WEAK_R,
  NORMAL_R,
  STRONG_R
}STATE;

typedef enum{
  ENTRY,
  DO,
  EXIT
}ACTION;

volatile STATE g_state = STOP;
ACTION g_action = ENTRY;

void motorRhythm(int resolution){
  for(int cnt = 0; cnt < 30; cnt++){
    motorSpeed(cnt * resolution);
    delay(100);
  }
}

void motorControl(bool in1, bool in2){
  digitalWrite(PIN_IN1, in1);
  digitalWrite(PIN_IN2, in2);
}

void motorSpeed(int motor_speed){
  if(motor_speed > 255){
    motor_speed = 0;
  }
  analogWrite(PIN_VREF, motor_speed); 
}

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
            setStateAction(WEAK_R, ENTRY);
            break;
        }
        break;
      case WEAK_R:
        switch(getAction()){
          case ENTRY:
            /* 弱リズムモード */
            motorControl(LOW, HIGH); /* モーターを反転する */
            setStateAction(WEAK_R, DO);
            break;
          case DO:
            motorRhythm(WEAK_RSL);
            break;
          case EXIT:
            setStateAction(NORMAL_R, ENTRY);
            break;
        }
        break;
      case NORMAL_R:
        switch(getAction()){
          case ENTRY:
            /* 中リズムモード */
            motorControl(LOW, HIGH); /* モーターを反転する */
            setStateAction(NORMAL_R, DO);
            break;
          case DO:
            motorRhythm(NORMAL_RSL);
            break;
          case EXIT:
            setStateAction(STRONG_R, ENTRY);
            break;
        }
        break;
      case STRONG_R:
        switch(getAction()){
          case ENTRY:
            /* 強リズムモード */
            motorControl(LOW, HIGH); /* モーターを反転する */
            setStateAction(STRONG_R, DO);
            break;
          case DO:
            motorRhythm(STRONG_RSL);
            break;
          case EXIT:
            setStateAction(STOP, ENTRY);
            break;
        }
        break;
    }
}
