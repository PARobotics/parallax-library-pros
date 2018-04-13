#ifndef LCD_C
#define LCD_C

/*
  LCD.c
  Takes care of LCD Selection and automatically displaying and update messages.

  TODO: Define constants lcdStr1 = {0}, lcdStr2 = {0}, lcdStrSide,
        lcdStrMode
  */

#ifndef USE_LCD
#define USE_LCD 0
#endif

#if USE_LCD == 1
/* INCLUDE IF ERROR WITH STRCPY/STRCMP!
static char *strcpy(char *destination, char *source)
{
    char *start = destination;

    while(*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0'; // add '\0' at the end
    return start;
}

static int strcmp(char *a, char *b)
{
    while (*a && *b && *a == *b) { ++a; ++b; }
    return (unsigned char)(*a) - (unsigned char)(*b);
}
*/

  void waitForPress(){
    while (lcdReadButtons(uart2) == 0) {} //If no buttons are pressed
    wait(5);
  }

  void waitForRelease(){
    while (lcdReadButtons(uart2) == 0) {} //If no buttons are pressed
    wait(5);
  }

  void lcdSelection() { //Function that handles the side and mode selection during pre auton
    
    //Clear the LCD
    lcdClear(uart2);

    lcdSetBacklight(uart2, 1);

    //Display filler text

    strcpy(lcdStr1, "Select Side:");
    strcpy(lcdStr2, "starting ...");
    lcdPrint(uart2, 1, lcdStr1);
    lcdPrint(uart2, 2, lcdStr2);

    lcdSideSelection(uart2);

    strcpy(lcdStr2, "wait for MODE selection ...");
    lcdPrint(uart2, 2, lcdStr2)

    delay(250);

    lcdModeSelection(uart2);
    lcdSetBacklight(uart2, 0);
  }

  void lcdSideSelection(){
    char *lcdLeftStr = "LEFT < RIGHT";
    char *lcdRightStr = "LEFT > RIGHT";

    //Cycle through sides until the center is pressed
    SIDE = LEFT; //Initialize the side
    strcpy(lcdStr2, lcdLeftStr);
    lcdPrint(uart2, 1, lcdStr2);

    while (lcdReadButtons(uart2) != 010) { //While center isn't pressed
      if(lcdReadButtons(uart2) == 100) //Check if left button is pressed
        SIDE = LEFT;
      else if(lcdReadButtons(uart2) == 001) //Check if right button is pressed
        SIDE = RIGHT;

      if (strcmp(lcdStr2, lcdLeftStr) == 0 && SIDE == RIGHT) {
        //If the right button is pressed but the LCD indicates left text
        strcpy(lcdStr2, lcdRightStr);
        lcdPrint(uart2, 1, lcdStr2);
      } else if (strcmp(lcdStr2, lcdRightStr) == 0 && SIDE == LEFT) {
        //If the left button is pressed but the LCD indicates right text
        strcpy(lcdStr2, lcdLeftStr);
        lcdPrint(uart2, 1, lcdStr2);
      }
      delay(5);
    }

    if (SIDE == RIGHT) strcpy(lcdStrSide, "R");
    if (SIDE == LEFT) strcpy(lcdStrSide, "L");
  }

  void lcdModeSelection(uart2){
    MODE = AUTO_A;

    strcpy(lcdStr1, "Select Mode:");
    lcdPrint(uart2, 1, lcdStr1);

    //While not selected:
    while (lcdReadButtons(uart2) != 010) { //While center isn't pressed
      //Cycle:
      if (MODE < 0) MODE = 6;
      if (MODE > 5) MODE = 0;
      if (MODE == AUTO_A) strcpy(lcdStrMode, "Auto A");
      if (MODE == AUTO_B) strcpy(lcdStrMode, "Auto B");
      if (MODE == AUTO_C) strcpy(lcdStrMode, "Auto C");
      if (MODE == RBT_SKILL) strcpy(lcdStrMode, "Rbt Skills");
      if (MODE == PRG_SKILL) strcpy(lcdStrMode, "Prg Skills");
      if (MODE == TESTING) strcpy(lcdStrMode, "Testing");

      char lcdStrSideMode[25] = {0};
      strcpy(lcdStrSideMode, lcdStrSide);
      strcat(lcdStrSideMode, " ");
      strcat(lcdStrSideMode, lcdStrMode);

      //Allow switching between modes
      lcdPrint(uart2, 1, lcdStrSideMode);

      waitForPress();
      if (lcdReadButtons(uart2) == 100){ //Left button
        waitForRelease();
        MODE--;
      }

      if (lcdReadButtons(uart2) == 001){ //Right button
        waitForRelease();
        MODE++;
      }
    }

    lcdGenerateMessage(); //Defined in config.c
    lcdPrint(uart2, 1, lcdStr1);
    lcdPrint(uart2, 2, lcdStr2);
  }

  void lcdMessage(){
    lcdGenerateMessage(); //Defined in config.c

    lcdPrint(uart2, 1, lcdStr1);
    lcdPrint(uart2, 2, lcdStr2);
  }

#endif

#endif
