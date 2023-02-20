#define LEDPIN 6     // LEDはピン3に接続

typedef enum{
  INCREASE,
  MAX
}STATE;

typedef enum{
  ENTRY,
  DO,
  EXIT
}ACTION;

STATE g_state = INCREASE;
ACTION g_action = ENTRY;
volatile int g_intensity = 0;     // 発光強度

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
  pinMode(LEDPIN,OUTPUT);     //アナログ出力を使うので　pinModeをOUTPUTに
  analogWrite(LEDPIN, 0);     //LEDの初期状態を消灯にする
  Serial.begin(9600);
}

void loop() {

  switch(getState())
  {
    case INCREASE:
      switch(getAction())
      {
        case ENTRY:
          setStateAction(INCREASE, DO);
          break;
        case DO:
          g_intensity++;                    //loop毎にインクリメント
          if(g_intensity >= 255){            //もしintensityが255以上なら
            setStateAction(INCREASE, EXIT);
          }
          analogWrite(LEDPIN, g_intensity);  //valの値に応じてLEDを点灯
          delay(10);
          break;
        case EXIT:
          setStateAction(MAX, ENTRY);
          break;
      }
      break;
    case MAX:
      switch(getAction())
      {
        case ENTRY:
          setStateAction(MAX, DO);
          break;
        case DO:
          delay(3000);
          setStateAction(MAX, EXIT);
          break;
        case EXIT:
          g_intensity = 0;
          analogWrite(LEDPIN, g_intensity);  //valの値に応じてLEDを点灯
          setStateAction(INCREASE, ENTRY);
          break;
      }
      break;    
  }
}
