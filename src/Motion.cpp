#include <Arduino.h>
#include "ObstacleDetect.h"
#include "Motion.h"
#include "ServoControl.h"

#define FAN_PIN 45 

// declare function output and function flag   
MOTION cruise_command;
int cruise_output_flag;
MOTION follow_command;
int follow_output_flag;
MOTION extinguish_command;
int extinguish_output_flag;
MOTION avoid_command;
int avoid_output_flag;
int motor_input;

// After reversing tell cruise to move left or right
int reversed_flag;

// cruise function output command and flag
void cruise()
{
  cruise_command = FORWARD;
  cruise_output_flag = 1;
  if (reversed_flag) {
    cruise_command = RIGHT_ARC;
  }
}

// follow function output command and flag
void follow()
{ // int delta;
  //float grey_photo, purple_photo, green_photo, blue_photo;
  // For now im assuming Grey is front, purple is right, green is back, blue is left
  //grey_photo = readPhotoGrey();
  // Do same for others
  //right_photo = ....if
  /*delta=photo_right - photo_left;
     if (abs(delta)>photo_dead_zone)
       {if (delta>0)
         follow_command=LEFT_TURN;
       else
         follow_command=RIGHT_TURN;
       follow_output_flag=1;
       }
     else
       follow_output_flag=0; */
}

// turn on fan until light goes out or for 10 seconds
void extinguish()
{
  extinguish_command = STOP;
}

// avoid function output command and flag
void avoid()
{
  int val;
  val = obstacle_detect();
  if (val == 2)
  {
    avoid_output_flag = 1;
    avoid_command = RIGHT_ARC;
  }
  else if (val == 3)
  {
    avoid_output_flag = 1;
    avoid_command = LEFT_ARC;
  }
  else if (val == 1)
  {
    avoid_output_flag = 1;
    avoid_command = BACKWARD;
    reversed_flag = 1;

  }
  else
  {
    avoid_output_flag = 0;
  }
}

// check flag and select command based on priority
void arbitrate()
{
  if (cruise_output_flag == 1)
  {
    motor_input = cruise_command;
  }
  if (follow_output_flag == 1)
  {
    motor_input = follow_command;
  }
  if (extinguish_output_flag == 1)
  {
    motor_input = extinguish_command;
  }
  if (avoid_output_flag == 1)
  {
    motor_input = avoid_command;
  }
  robot_move();
}

// connect the selected commands to the robot motions
void robot_move()
{
  switch (motor_input)
  {
  case FORWARD:
    forward();
    delay(1000);
    break;

  case BACKWARD:
    reverse();
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
