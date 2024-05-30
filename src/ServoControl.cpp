#include <Servo.h>
#include "ServoControl.h"
#include <Arduino.h>
#include "Phototransistor.h"

Servo left_front_motor;   // create servo object to control Vex Motor Controller 29
Servo left_rear_motor;   // create servo object to control Vex Motor Controller 29
Servo right_rear_motor;  // create servo object to control Vex Motor Controller 29
Servo right_front_motor;  // create servo object to control Vex Motor Controller 29
Servo uss_servo;

// intialise speed values
int speed_val = 165;    //175
int turn_val = 95;      //75
int speed_change;

void servo_setup() {
  // Attatch servo motors
  left_front_motor.attach(left_front);
  left_rear_motor.attach(left_rear);
  right_rear_motor.attach(right_rear);
  right_front_motor.attach(right_front);
  uss_servo.attach(uss_servo_pin);
}

void speed_change_smooth()                  // change speed, called in RUNING STATE
{
  speed_val += speed_change;                  // speed value add on speed change 
   if(speed_val > 500)                          // make sure speed change less than 1000
   speed_val = 500;
   speed_change = 0;    //make speed change equals 0 after updating the speed value 
}

void disable_motors(){                             // function disable all motors, called in  STOPPED STATE
  left_front_motor.detach();
  left_rear_motor.detach();
  right_rear_motor.detach();
  right_front_motor.detach();

  pinMode(left_front,INPUT);                   // set pinMode for next step 
  pinMode(left_rear,INPUT);
  pinMode(right_rear,INPUT);
  pinMode(right_front,INPUT);
}

void enable_motors() {                                //enable all motors, was called in INITIALZING SATE 
  left_front_motor.attach(left_front);
  left_rear_motor.attach(left_rear);
  right_rear_motor.attach(right_rear);
  right_front_motor.attach(right_front);
}

void stop(){                                                                // stop motors 
  left_front_motor.writeMicroseconds(1500);
  left_rear_motor.writeMicroseconds(1500);
  right_rear_motor.writeMicroseconds(1500);
  right_front_motor.writeMicroseconds(1500);
}
void forward(){                                                         // moving forward  
  left_front_motor.writeMicroseconds(1500 + speed_val);
  left_rear_motor.writeMicroseconds(1500 + speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_front_motor.writeMicroseconds(1500 - speed_val);
}

void reverse(){                                                                  // reverse  
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_front_motor.writeMicroseconds(1500 + speed_val);
}
void strafe_left(){                                                         // straight left  
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 + speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_front_motor.writeMicroseconds(1500 - speed_val);
}
void strafe_right(){                                                  //straight right  
  left_front_motor.writeMicroseconds(1500 + speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_front_motor.writeMicroseconds(1500 + speed_val);
}
void cw(){                                                                   //clockwise  
  left_front_motor.writeMicroseconds(1500 + turn_val);
  left_rear_motor.writeMicroseconds(1500 + turn_val);
  right_rear_motor.writeMicroseconds(1500 + turn_val);
  right_front_motor.writeMicroseconds(1500 + turn_val);
}
void ccw(){                                                              //anticlockwise  
  left_front_motor.writeMicroseconds(1500 - turn_val);
  left_rear_motor.writeMicroseconds(1500 - turn_val);
  right_rear_motor.writeMicroseconds(1500 - turn_val);
  right_front_motor.writeMicroseconds(1500 - turn_val);
}

void reverse_ccw()
{
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_front_motor.writeMicroseconds(1500 + speed_val);
  delay(100);
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_front_motor.writeMicroseconds(1500 - speed_val);
}

void turn_180() {
  left_front_motor.writeMicroseconds(1500 - 175);
  left_rear_motor.writeMicroseconds(1500 - 175);
  right_rear_motor.writeMicroseconds(1500 - 175);
  right_front_motor.writeMicroseconds(1500 - 175);
  delay(2500);
}

void turn_fan(int val) {
  
  if (val == 1) {
    uss_servo.write(90);
  }
  if (val == 2) {
    uss_servo.write(60);
  }
  if (val == 3) {
    uss_servo.write(120);
  }
}