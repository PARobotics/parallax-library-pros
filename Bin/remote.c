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

  typedef struct{
    char joystick;
    char buttonGroup;
    char button;

    int pushed;  // temporary variable to hold that the button has been pushed
    int status;  // 1: yes push and released; 0 no
    int timePushed;
  } PRB_type;

  static PRB_type PRB[NUM_PR_BUTTONS];

  void updatePrbStatus(){
    int sv = 0;     // temp variable to hold sensor value
    for(int i = 0; i < NUM_PR_BUTTONS; i++){
      sv = joystickGetDigital(PRB[i].joystick, PRB[i].buttonGroup, PRB[i].button);

      // When button is pushed
      if (sv == 1){
      	if(PRB[i].pushed == 0) PRB[i].timePushed = millis(); //TODO Where is time1[T1] defined
        PRB[i].pushed = 1;
      }
      // Alreay pushed and now released
      if (sv == 0 && PRB[i].pushed == 1){
        PRB[i].pushed = 0;
        if(millis() - PRB[i].timePushed >= 1000){
          #if DEBUG == 1 || DEBUG_REMOTE == 1
            printf("[REMOTE] Button %d has been long held", i);
          #endif
          PRB[i].status = 2;
        }
        else {
          #if DEBUG == 1 || DEBUG_REMOTE == 1
            printf("[REMOTE] Button %d has been pushed and released", i);
          #endif
          PRB[i].status = 1;
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
    PRB[i].status = 0;
  }

#endif

#endif
