#define LEDPIN 3     // LEDはピン3に接続
#define INPIN 0   // 割り込みピン2
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

STATE g_state = WEAK;
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

void changeIntensity(){
  setAction(EXIT);
}

void setup() {
  pinMode(LEDPIN, OUTPUT);   // アナログ出力なので　出力を設定
  analogWrite(LEDPIN, 0);    // ledの初期状態を消灯にする
  attachInterrupt(INPIN, changeIntensity, RISING);
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
          break;
        case EXIT:
          setStateAction(WEAK, ENTRY);
          break;
      }
      break;
  }
}
