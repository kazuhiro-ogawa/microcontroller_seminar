#define LEDPIN 3     // LEDはピン3に接続
#define LED_WEAK 16
#define LED_MEDIUM 128
#define LED_STRONG 255

typedef enum{
  WEAK,
  MEDIUM,
  STRONG,
  OFF
}STATE;

typedef enum{
  ENTRY,
  DO,
  EXIT
}ACTION;

STATE g_state = OFF;
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

void setup() {
  pinMode(LEDPIN,OUTPUT);   //アナログ出力の場合 デジタルピンを使うのでpinMode()が必要
  analogWrite(LEDPIN, 0);   //アナログ出力の初期値を0にする
  Serial.begin(9600);
}

void loop() {
  
    switch(getState())   
    {
      case WEAK:
        switch(getAction()){
          case ENTRY:
            analogWrite(LEDPIN, LED_WEAK);    //LEDを弱点灯
            setStateAction(WEAK, DO);
            break;
          case DO:
            setStateAction(WEAK, EXIT);
            delay(1000);
            break;
          case EXIT:
            setStateAction(MEDIUM, ENTRY);
            break;
        }
        break;
      case MEDIUM:
        switch(getAction()){
          case ENTRY:
            analogWrite(LEDPIN, LED_MEDIUM);   //LEDを中点灯
            setStateAction(MEDIUM, DO);
            break;
          case DO:
            setStateAction(MEDIUM, EXIT);
            delay(1000);
            break;
          case EXIT:
            setStateAction(STRONG, ENTRY);
            break;
        }
        break;
      case STRONG:
        switch(getAction()){
          case ENTRY:
            analogWrite(LEDPIN, LED_STRONG);   //LEDを強点灯(255・・・5V）
            setStateAction(STRONG, DO);
            break;
          case DO:
            setStateAction(STRONG, EXIT);
            delay(1000);
            break;
          case EXIT:
            setStateAction(OFF, ENTRY);
            break;
        }       
        break;
      case OFF:
        switch(getAction()){
          case ENTRY:
            analogWrite(LEDPIN, 0);     //LEDを消灯(0 ・・・　0V）
            setStateAction(OFF, DO);
            break;
          case DO:
            setStateAction(OFF, EXIT);
            delay(1000);
            break;
          case EXIT:
            setStateAction(WEAK, ENTRY);
            break;
        }
        break;
    }
}
