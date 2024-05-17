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
int speed_val = 110;
int speed_change;

void servo_setup() {
  // Attatch servo motors
  left_front_motor.attach(left_front);
  left_rear_motor.attach(left_rear);
  right_rear_motor.attach(right_rear);
  right_front_motor.attach(right_front);
  uss_servo.attach(uss_servo_pin);
}

int fan_servo_calib() {
  float a = read_front();  // Left
  float b = read_left(); // Left Diagonal
  float c = read_right(); // Right Diagonal
  float d = read_back(); // Right

  float highest = max(max(a, b), max(c, d));

   if (highest == a) {
    uss_servo.write(FRONT);
    highest = 1;
  } else if (highest == b) {
    uss_servo.write(LEFT);
    highest = 2;
  } else if (highest == c) {
    uss_servo.write(RIGHT);
    highest = 3;
  } else if (highest == d) {
    uss_servo.write(45);
    highest = 4;
  }

  return highest;
  
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
  left_front_motor.writeMicroseconds(1500 + speed_val);
  left_rear_motor.writeMicroseconds(1500 + speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_front_motor.writeMicroseconds(1500 + speed_val);
}
void ccw(){                                                              //anticlockwise  
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_front_motor.writeMicroseconds(1500 - speed_val);
}

void reverse_ccw()
{
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_front_motor.writeMicroseconds(1500 + speed_val);
  delay(500);
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_front_motor.writeMicroseconds(1500 - speed_val);
}