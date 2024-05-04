#ifndef SERVOCONTROL_H_
#define SERVOCONTROL_H_

void servo_setup();
void speed_change_smooth();
void disable_motors();
void enable_motors();
void stop();
void forward();
void reverse();
void strafe_left();
void strafe_right();
void cw();
void ccw();
void reverse_ccw();
#endif