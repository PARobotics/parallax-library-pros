#ifndef REMOTE_C
#define REMOTE_C

#ifndef DEBUG_REMOTE
  #define DEBUG_REMOTE 0
#endif

#ifndef NUM_PR_BUTTONS
  #define NUM_PR_BUTTONS 0
#endif

#if USE_PR_BUTTON == 1

  #define PUSHED_RELEASED 1
  #define LONG_HELD 2
  #define DOUBLE_PRESS 3
  #define TRANSITION_STATE -1

#define DOUBLE_PRESS_TIME 200
#define LONG_PRESS_TIME 1000

  typedef struct{
    char joystick;
    char buttonGroup;
    char button;

    int pushed;  // temporary variable to hold that the button has been pushed
    int status;  // 3: double; 2: long pushed; 1: yes push and released; 0: no; -1: within the time allot
    int timePushed;
    int timeReleased;
  } PRB_type;

  static PRB_type PRB[NUM_PR_BUTTONS];

  void updatePrbStatus(){
    int sv = 0;     // temp variable to hold sensor value
    for(int i = 0; i < NUM_PR_BUTTONS; i++){
      sv = joystickGetDigital(PRB[i].joystick, PRB[i].buttonGroup, PRB[i].button);

      // When button is pushed
      if (PRB[i].status == TRANSITION_STATE){
        if(millis() - PRB[i].timeReleased() >= DOUBLE_PRESS_TIME){
            PRB[i].status = 0;
        }
      }
      if (sv == 1){
      	if(PRB[i].pushed == 0) PRB[i].timePushed = millis(); //TODO Where is time1[T1] defined
        PRB[i].pushed = 1;
      }
      // Already pushed and now released
      if (sv == 0 && PRB[i].pushed == 1){
        PRB[i].timeReleased = millis();
        PRB[i].pushed = 0;
        if(PRB[i].status() == -1){
            #if DEBUG == 1 || DEBUG_REMOTE == 1
                printf("[REMOTE] Button %d has been double pressed", i);
            #endif
            PRB[i].status = DOUBLE_PRESS;
        }
        else if(millis() - PRB[i].timePushed >= LONG_PRESS_TIME){
          #if DEBUG == 1 || DEBUG_REMOTE == 1
            printf("[REMOTE] Button %d has been long held", i);
          #endif
          PRB[i].status = LONG_HELD;
        }
        else {
          #if DEBUG == 1 || DEBUG_REMOTE == 1
            printf("[REMOTE] Button %d has been pushed and released", i);
          #endif
          PRB[i].status = PUSHED_RELEASED;
        }
      }
    }
  }

  void addPrButton(int i, char jt, char bg, char b){
    PRB[i].joystick = jt;
    PRB[i].buttonGroup = bg;
    PRB[i].button = b;
  }

  int getPrButton(int i){
    return PRB[i].status;
  }

  void resetPrButton(int i){
    if(PRB[i].status == PUSHED_RELASED) PRB[i].status = TRANSITION_STATE;
    else PRB[i].status = 0;
  }

#endif

#endif
