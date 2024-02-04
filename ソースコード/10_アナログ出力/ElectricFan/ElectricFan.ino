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

void setup(){
  attachInterrupt(PIN_SW, changeMode, FALLING);       /* SWはD2で割り込み */

  pinMode(PIN_IN1,OUTPUT);      /* 回転方向制御 */
  pinMode(PIN_IN2,OUTPUT);      /* 回転方向制御 */
  pinMode(PIN_VREF,OUTPUT);     /* 回転速度制御 */
  
  analogWrite(PIN_VREF,0);      /* モーターの回転速度を0にする(急に動き出さないように) */
  digitalWrite(PIN_IN1,LOW);    /* 最初はLOWにしとく */
  digitalWrite(PIN_IN2,LOW);    /* 最初はLOWにしとく */

  Serial.begin(9600);
}
 
void loop(){
  
    //Serial.println(g_state);

    switch(getState()){
      case STOP:
        switch(getAction()){
          case ENTRY:
            /* 停止モード */
            digitalWrite(PIN_IN1,LOW);  /* モーターを停止する */
            digitalWrite(PIN_IN2,LOW);
            analogWrite(PIN_VREF,0);
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
            digitalWrite(PIN_IN1,LOW); /* モーターを反転する */
            digitalWrite(PIN_IN2,HIGH);
            analogWrite(PIN_VREF,90);
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
            digitalWrite(PIN_IN1,LOW); /* モーターを反転する */
            digitalWrite(PIN_IN2,HIGH);
            analogWrite(PIN_VREF,150);
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
            digitalWrite(PIN_IN1,LOW); /* モーターを反転する */
            digitalWrite(PIN_IN2,HIGH);
            analogWrite(PIN_VREF,220);
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
