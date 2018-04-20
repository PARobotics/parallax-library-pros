#ifndef CONSTANTS_H
#define CONSTANTS_H

#define true 1
#define false 0
#define TASK_DEFAULT_STACK_SIZE 512
#define YES             1
#define NO              0
#define START					  1
#define STOP            0
#define MONITOR         2
#define LEFT           -1
#define RIGHT           1
#define FWD             1
#define BKWD           -1
#define UP              1
#define DOWN           -1
#define MANUAL_UP       2
#define MANUAL_DOWN     3
#define MANUAL 15
#define HOLD            4
#define CARRY           5
#define MOVE            6
#define IN              1
#define OUT            -1
#define OPEN            1
#define CLOSE           -1
#define AUTO_A          0
#define AUTO_B          1
#define AUTO_C          2
#define PRG_SKILL       3
#define RBT_SKILL       4
#define TESTING         5
#define TOGGLE          2
#define CLOCKWISE       1
#define COUNTERCLOCKWISE -1
#define ON 1
#define OFF 0
#define BLINK 3
#define ARRAY_MAX 25

// LCD
//int MODE = AUTO_A;
//int SIDE = LEFT;         // Blue or Red side that is selected
extern int MODE;
extern int SIDE;         // Blue or Red side that is selected

char lcdStr1[ARRAY_MAX];                // hold the 16 character string for LCD line 1
char lcdStr2[ARRAY_MAX];                // hold the 16 character string for LCD line 2
char lcdStrSide[ARRAY_MAX];             // 'B' or 'R' indicates the field selection
char lcdStrMode[ARRAY_MAX];             // lcdStr for Mode

#define LEFTBUTTON     1
#define CENTERBUTTON   2
#define RIGHTBUTTON    4

//Bailout
//int BAILOUT = 0;
extern int BAILOUT;

/*
	CONTROL, SENSORS
*/


// Constants
#define RPM_393_HS    392      // # ticks per revolution
#define RPM_393       627.2
#define RPM_SE        360


//Motor Monitor
#define M_PI 3.1415926535897932384626433832795

/*
	Wrapper Functions
*/

//Slew
#define kNumbOfTotalMotors 10 // from robotC, set val to 10
#define MOTOR_NUM kNumbOfTotalMotors


int motorReq[kNumbOfTotalMotors];     //Array to hold requested speed for the motors


// sensors struct
typedef struct {
  short port;    // port number where the sensor is coupled
  float scalingFactor;      // conversion factor   raw measurement to physical measurements
  short motor; // motor index
  int raw;     // raw sensor reading (SensorValue …)
  int val;        // scaled sensor value
  int speed;
  short dt;     // sampling interval
  short t;
  short tlast;
  int analog; // 1 == analog, 0 == digital
} Sensor;


//Sensors
void sensorReset();
int getMainBatteryVoltage();
int getSecondBatteryVoltage();
void sensorUpdate(&Sensor);
//void makeLED(tSensors p, int status);
//void initializeSensor(sensor* s, float sF, tSensors p);
//void initializeSensor(sensor* s, float sF, tSensors p, pid PID);
//void updateSensorValue(sensor* s);
//int getSensorVCMD(sensor* s, int pe, int se);
//int sensorHold(sensor* s, int target, int v_default, int v_min, int v_max);
//TODO: figure out how to do overriding in c
//TODO: uncomment all this once sensors are added to lib
//int sensorHold(sensor* s, int target, int v_default);
//int sensorPControl(sensor* s, int target);
//int sensorPDControl(sensor* s, int to_target, int v_target);

//LCD
void waitForPress();
void waitForRelease();
void lcdSelection();
void lcdSideSelection();
void lcdModeSelection();
void lcdMessage();

//Remote
void updatePrbStatus();
void addPrButton(int i, int port);
int getPrButton(int i);
void resetPrButton(int i);

//Bailout
void bailOut();
int isTimedOut(unsigned long tstop);




//Competition Procedure
void libinitialize();
void userControlProcedure();
void preAutonProcedure();
void autonProcedure(void);
void userControlUpdate(void);











#endif
