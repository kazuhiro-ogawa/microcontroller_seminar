
typedef enum{
/* ここに状態（ステート）記述 */
}STATE;

typedef enum{
  ENTRY,
  DO,
  EXIT
}ACTION;

/* g_stateには最初の状態を記述 */
STATE g_state = ;
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

}

void loop() {
  
    switch(getState())   
    {
      case /*ここに状態を記述*/:
        switch(getAction()){
          case ENTRY:
            setStateAction(, DO);
            break;
          case DO:
            setStateAction(, EXIT);
            break;
          case EXIT:
            setStateAction(, ENTRY);
            break;
        }
        break;

        /* 他にも状態があれば以下にcase文を追加していく */
    }
}
