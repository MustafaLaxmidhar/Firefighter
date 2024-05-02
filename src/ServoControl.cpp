#include <Servo.h>
#include <Arduino.h>

// Motor Setup
// Default motor control pins
#define left_front 46
#define left_rear 47
#define right_rear 50
#define right_front 51
#define uss_servo_pin 11

Servo left_font_motor;   // create servo object to control Vex Motor Controller 29
Servo left_rear_motor;   // create servo object to control Vex Motor Controller 29
Servo right_rear_motor;  // create servo object to control Vex Motor Controller 29
Servo right_font_motor;  // create servo object to control Vex Motor Controller 29
Servo uss_servo;

// Uss servo positions
#define FRONT 83
#define RIGHT 0
#define LEFT 180

void servo_setup() {
  // Attatch servo motors
  left_font_motor.attach(left_front);
  left_rear_motor.attach(left_rear);
  right_rear_motor.attach(right_rear);
  right_font_motor.attach(right_front);
  uss_servo.attach(uss_servo_pin);
}