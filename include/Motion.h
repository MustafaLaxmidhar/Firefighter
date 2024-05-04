#ifndef MOTION_H
#define MOTION_H

// declare function output and function flag   
MOTION cruise_command();
int cruise_output_flag;
MOTION follow_command();
int follow_output_flag;
MOTION extinguish_command();
int extinguish_output_flag;
MOTION avoid_command();
int avoid_output_flag;
MOTION motor_input();

void crusie();
void follow();
void extinguish();
void avoid();

#endif