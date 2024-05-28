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


// cruise function output command and flag
void cruise()
{
  cruise_command = LEFT_TURN;
  cruise_output_flag = 1;
}

// follow function output command and flag
void follow()
{ 
  int val = find_fire();

  if (val == 1)
  {
    follow_output_flag = 1;
    follow_command = LEFT_TURN;
  }
  else if (val == 2)
  {
    follow_output_flag = 1;
    follow_command = RIGHT_TURN;
  }
  else if (val == 3)
  {
    follow_output_flag = 1;
    follow_command = FORWARD;
  }
  else if (val == 4)
  {
    follow_output_flag = 1;
    follow_command = TURN_AROUND;
  }
  else
  {
    follow_output_flag = 0;
  }
}

// turn on fan until light goes out or for 10 seconds
void extinguish()
{
  int val = find_fire();
  if (val == 5)
  {
    extinguish_output_flag = 1;
    extinguish_command = STOP;
  }

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
  }else if (val == 4)
  {
    avoid_output_flag = 1;
    avoid_command = BACKWARD_LEFT_TURN;
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
  if (avoid_output_flag == 1)
  {
    motor_input = avoid_command;
  }
  if (extinguish_output_flag == 1)
  {
    motor_input = extinguish_command;
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
    delay(50);
    break;

  case BACKWARD:
    reverse();
    delay(50);
    break;

  case LEFT_TURN:
    ccw();
    delay(25);
    break;

  case RIGHT_TURN:
    cw();
    delay(25);
    break;

  case LEFT_ARC:
    strafe_left();
    delay(50);
    break;

  case RIGHT_ARC:
    strafe_right();
    delay(50);
    break;

  case BACKWARD_LEFT_TURN:
    reverse_ccw();
    delay(50);
    break;

  case TURN_AROUND:
    turn_180();
    delay(50);
    break;
  
  case STOP:
   stop();
   delay(50);
  }
}

