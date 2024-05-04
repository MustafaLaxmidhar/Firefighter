// define motions states 
enum MOTION{
FORWARD,
BACKWARD,
LEFT_TURN,
RIGHT_TURN,
LEFT_ARC,
RIGHT_ARC,
BACKWARD_LEFT_TURN,
STOP
};

// cruise function output command and flag
void cruise()
{
  cruise_command = FORWARD;
  cruise_output_flag=1; 
}

// follow function output command and flag
void follow()
{ int delta;
  //int left_photo, right_photo, delta;
    //left_photo=analog(1);
   // right_photo=analog(0);
    delta=photo_right - photo_left;
    if (abs(delta)>photo_dead_zone)
      {if (delta>0)
        follow_command=LEFT_TURN;
      else 
        follow_command=RIGHT_TURN;
      follow_output_flag=1;
      }
    else
      follow_output_flag=0;
             
}

// turn on fan until light goes out or for 10 seconds
void extinguish()
{
  extinguish_command = STOP;
}

// avoid function output command and flag 
void avoid()
{int val;
     val=ir_detect;
    //val=ir_detect();
    if (val==1)
      {avoid_output_flag=1;
      avoid_command=BACKWARD;}
    else if (val==2)
      {avoid_output_flag=1;
      avoid_command=RIGHT_ARC;}
    else if (val==3)
      {avoid_output_flag=1;
      avoid_command=LEFT_ARC;}
    else
      {avoid_output_flag=0;}
     
 }

// check flag and select command based on priority 
void arbitrate ()
 {
  if (cruise_output_flag==1)
  {motor_input=cruise_command;}
  if (follow_output_flag==1)
  {motor_input=follow_command;}
  if (extinguish_output_flag ==1)
  {motor_input=extinguish_command;}
  if (avoid_output_flag ==1)
  {motor_input=avoid_command;}
  robotMove();                                    
  }

// connect the selected commands to the robot motions 
void robotMove()
{
switch(motor_input)
{
  case FORWARD:
  forward ();
  delay(1000);
  break;
  
  case BACKWARD:
  reverse ();
  delay(1000);
  break;
  
  case LEFT_TURN:
  ccw();
 delay(1000);
  break;
 
  case RIGHT_TURN:
  cw();
 delay(1000);
  break;
 
  case LEFT_ARC:
  strafe_left();
  delay(1000);
  break;
 
  case RIGHT_ARC:
  strafe_right();
   delay(1000);
  break;

  case BACKWARD_LEFT_TURN:
  reverse_ccw();
  delay(1000);
  break;

  case STOP:
  stop();
  delay(1000);
  }
}