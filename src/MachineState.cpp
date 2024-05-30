#include <SoftwareSerial.h>
#include <Arduino.h>
#include "Motion.h"
#include "ServoControl.h"
#include "MachineState.h"

// Serial Pointer
HardwareSerial *SerialCom;

// Previous State holder
bool extinguish_flag = false;
bool previous_extinguish_flag = false;

int iLikeDick = 0;

//====================================================================== functions with machine STATE outputs ====================================================//

STATE initialising(){
  enable_motors();                                 // enable motors 
  return RUNNING;                               // return to RUNING STATE DIRECTLY 
}

STATE running(){
  //read_serial_command();                      // read command from serial communication 
  speed_change_smooth();                 //function to speed up and slow down smoothly 
  // four function 
  cruise();
  follow(); 
  extinguish();
  avoid(); 
  // select the output command based on the function priority 
  int state = arbitrate();

  previous_extinguish_flag = extinguish_flag;

  if (state == 4) {
    extinguish_flag = true;
    delay(50);
  }else {
    extinguish_flag = false;
  }

  if (!extinguish_flag && previous_extinguish_flag) {
    iLikeDick++;
  }
  if (iLikeDick == 2) {
    return STOPPED;
  }
    
  return RUNNING;   // return to RUNNING STATE again, it will run the RUNNING    
                   
}                                                            // STATE REPEATLY 

STATE stopped(){
  disable_motors();                           // disable the motors
  return STOPPED; 
}

int getFireCounts(){
  return iLikeDick;
}