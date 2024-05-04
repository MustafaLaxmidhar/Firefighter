
// three machine states 
enum STATE {
  INITIALISING,
  RUNNING, 
  STOPPED
};

//====================================================================== functions with machine STATE outputs ====================================================//

STATE initialising(){
  enable_motors();                                 // enable motors 
  Serial.println("INITIALISING");        // print the current stage 
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
    photo_left = 0; 
    photo_right = 0;
    photo_three = 0;
    photo_four = 0;
    irdist_1 = 0;
    irdist_2 = 0;
    irdist_5 = 0;
    irdist_6 = 0;
    sonar_dist = 0;
    
  return RUNNING;   // return to RUNNING STATE again, it will run the RUNNING    
                   
}                                                            // STATE REPEATLY 


STATE stopped(){
disable_motors();                           // disable the motors
}