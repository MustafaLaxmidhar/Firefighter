#include <SoftwareSerial.h>
#include <Arduino.h>
#include "Motion.h"
#include "ServoControl.h"
#include "MachineState.h"

// Serial Pointer
HardwareSerial *SerialCom;

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
  arbitrate();
    
  return RUNNING;   // return to RUNNING STATE again, it will run the RUNNING    
                   
}                                                            // STATE REPEATLY 

STATE stopped(){
  disable_motors();                           // disable the motors
  return STOPPED; 
}