#include <Arduino.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include "Sonar.h"
#include "Infrared.h"
#include "Gyro.h"
#include "ServoControl.h"
#include "Phototransistor.h"
#include "MachineState.h"
#include "Motion.h"
#include "ObstacleDetect.h"

// Serial Pointer
extern HardwareSerial *SerialCom;
int lightCount = 0;
int prev_front_PT = 0;
int prev_val = 0;

// Gyro zero angle voltage
static float gyro_zero_calibration;

extern int iLikeDick;

void setup()
{
  //startup delay
  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);
  delay(3000);
  digitalWrite(45, LOW);

  // Bluetooth
  SerialCom = &Serial1;
  SerialCom->begin(115200);

  // neccessary setups
  sonar_setup();
  ir_setup();
  servo_setup();

  // Gyro
  pinMode(A15, INPUT);
  gyro_zero_calibration = gyro_calibration();

  // start MSG
  SerialCom->println("Start");
}

void loop()
{
  int val = obstacle_detect();
  int val2 = find_fire();
  int right_front_PT = front_right();
  int front_PT = read_front();
  int back_PT = read_back(); 
  int left_front_PT = front_left();
  float front = measure_sonar();
  float b = measure_dist2();       // Left Diagonal
  float c = measure_dist1();       // Right Diagonal

  SerialCom->println("------------------------------------");
  SerialCom->print("Obstacle: "); SerialCom->println(val);
  SerialCom->print("FindFire: "); SerialCom->println(val2);
  SerialCom->println(" ");
  SerialCom->print("right_front_PT is: "); SerialCom->println(right_front_PT);
  SerialCom->print("left_front_PT is: "); SerialCom->println(left_front_PT);
  SerialCom->print("back is: "); SerialCom->println(back_PT);
  SerialCom->print("front is: "); SerialCom->println(front_PT);
  SerialCom->print("front dist is: "); SerialCom->println(front);
  SerialCom->print("left diag dist is: "); SerialCom->println(b);
  SerialCom->print("right diag dist is: "); SerialCom->println(c);
  SerialCom->print("Fire Counts is: "); SerialCom->println(getFireCounts());
  SerialCom->println(" ");

static STATE machine_state = INITIALISING;     // start from the sate INITIALIING 
switch (machine_state)
{
  case INITIALISING:
     machine_state = initialising();
     break;
  case RUNNING:
     machine_state = running();
     break;
  case STOPPED:
     machine_state = stopped();
     break;
}

}