#ifndef FUNCTION_C
#define FUNCTION_C

#include "../include/API.H"

/*
  Functions.c
  Commonly used functions
*/

// ** Utility Functions **
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define SIGN(X)   ( ((X) > 0) ? (1) : ( ((X) < 0) ? (-1) : (0) ) )
#define BOUND(A,AMIN,AMAX) MIN(AMAX,MAX(A,AMIN))

// ** Exit logic **
bool isTimedOut(unsigned long tstop){ // Check if timed out
  return millis() >= tstop;
}

bool isBailedOut(){ // Check if bailed out
  #ifdef BAILOUT_BUTTON
      return joystickGetDigital (1, BAILOUT_BUTTON, BAILOUT_BUTTONGROUP) == 1;
  #else
     return false;
  #endif
}

#endif
