#ifndef LIB_MAIN_C
#define LIB_MAIN_C

/*
  MAIN.C
  Implements and combines other library files
  *** Include this file ***
*/

#include "Bin/constants.h"
#include "Bin/functions.c"
#include "Bin/API.h"
//#include "../config.c" //You write this file

#ifndef DEBUG
  #define DEBUG 0
#endif

#include "bin/sensors.c"
#include "bin/remote.c"
#include "bin/slew.c"
#include "bin/lcd.c"
#include "bin/move.c"

void initialize(){

  bStopTasksBetweenModes = false;
  sensorReset();

  #if USE_PR_BUTTON == 1
    #if DEBUG == 1 || DEBUG_REMOTE == 1
      printf("Setting up remote buttons");
    #endif
    setUpButtons();
    #if DEBUG == 1 || DEBUG_REMOTE == 1
      printf("Successfully set up remote buttons");
    #endif
  #endif

  #if USE_SLEW == 1
    #if DEBUG == 1 || DEBUG_SLEW == 1
      printf("Slew task is enabled");
    #endif
    TaskHandle MotorSlewRateTask = taskCreate(MotorSlewRate, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

  #else
    #if DEBUG == 1 || DEBUG_SLEW == 1
      printf("Slew task is disabled");
    #endif
    TaskHandle MotorsTaskHandle = taskCreate(motorsTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

  #endif

  #if USE_MOVE == 1
    TaskHandle moveTaskHandle = taskCreate(moveTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

  #endif

  #if USE_LCD == 1
    lcdSelection();
  #endif

  preAutonProcedure();


  lcdInit(uart2);
  lcdClear(uart2);

}

void autonProcedure(){
  taskDelete(usercontrol);

	#if USE_LCD == 1
    if (MODE == AUTO_A) autoA();
    else if (MODE == AUTO_B) autoB();
  	else if (MODE == AUTO_C) autoC();
  	else if (MODE == PRG_SKILL) prgSkills();
    lcdMessage();
  #endif
}

void userControlUpdate(){
  #if USE_LCD == 1
    lcdMessage();
  #endif

  #if USE_PR_BUTTON == 1
    updatePrbStatus();
  #endif

  #ifdef BAILOUT_BUTTON
    if(joystickGetDigital (1, BAILOUT_BUTTON, BAILOUT_BUTTONGROUP)){ //TODO add BAILOUT_BUTTONGROUP
      #if DEBUG == 1 || DEBUG_REMOTE == 1
        printf("Bailout button pressed");
      #endif

      for(int i = 1; i < 11; i++) motorSet (i, 0);

      BAILOUT = 1;
      bailOut();
    }
    else
      BAILOUT = 0;
  #endif

  userControlProcedure();

  delay(10);
}

#endif
