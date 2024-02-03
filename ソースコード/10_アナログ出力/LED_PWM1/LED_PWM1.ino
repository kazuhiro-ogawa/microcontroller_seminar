#define LEDPIN 3     // LEDはピン3に接続

typedef enum{
  UP,
  MAX
}STATE;

typedef enum{
  ENTRY,
  DO,
  EXIT
}ACTION;

STATE g_state = UP;
ACTION g_action = ENTRY;
int g_intensity = 0;     // 発光強度

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
    case UP:
      switch(getAction())
      {
        case ENTRY:
          setStateAction(UP, DO);
          break;
        case DO:
          g_intensity++;                    //loop毎にインクリメント
          if(g_intensity >= 255){            //もしintensityが255以上なら
            setStateAction(UP, EXIT);
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
          setStateAction(UP, ENTRY);
          break;
      }
      break;    
  }
}
