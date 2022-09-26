#include <AccelStepper.h>

const int revolution = 4096;  
//motor steps for a full revolution
const int in1 = 5;
const int in2 = 4;
const int in3 = 0;
const int in4 = 2 ;
//pins on motor driver connected to micro controller
int prevposition = 1;
//must be updated before position is. Starts assuming blinds in open position
int position = 2;
//0 is cold side, 1 is open, 2 is warm side.
int targettemp = 25;
int temp = 25;
//as determind by temperature sensor
bool light = true;
// variable for if the sun is out as determined by light sensor
int mode = 1;
// 0 = manual, 1 = by target temp, 2 = automatic
const int revsbtwnstates = 2; 
// revolutions of motor needed between states, ie from cold to open and open to warm

AccelStepper motor(AccelStepper::HALF4WIRE, in1, in3, in2, in4);

void setup() {
  motor.setAcceleration(100);
  motor.setMaxSpeed(500);
  //sets maximum speed and acceleration of the motor
}

void loop() {
  if (mode = 0) {
    position = automode();
  }
  if (mode = 1) {
    position = tempmode();
  }
  if (mode = 2) {
    position = manualmode();
  }
  //check which mode it is in and runs the corresponding function

  if (position != prevposition) {
    motor.moveTo((position-prevposition)*revsbtwnstates*revolution);
  }
  //moves from current position to desired position

  motor.run();
  prevposition = position;
  //sets prevposition to current one
}

int tempmode() {
  if (temp < targettemp) {
    return 2; 
  }
  else if (temp > targettemp){
    return 0;
  }
  else {
    return prevposition;
  }
  //returns value which should be put into position
}

int automode() {
  if (sun = true) {
    return 1;
  }
  if (sun = false) {
    return 0; 
    // It might be annoying to have the reflective side inside so I decided to have it facing out at night.
  }
  //returns value which should be put into position
}

int manualmode() {
  //todo, connection to website needed here
}
