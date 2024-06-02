#ifndef SERVOCONTROL_H_
#define SERVOCONTROL_H_

// Uss servo positions
#define FRONT 83
#define RIGHT 0
#define LEFT 180

// Motor Setup
// Default motor control pins
#define left_front 46
#define left_rear 47
#define right_rear 50
#define right_front 51
#define uss_servo_pin 11

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
void turn_180();
void turn_fan(int val);

#endif