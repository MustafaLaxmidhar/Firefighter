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

// Gyro zero angle voltage
static float gyro_zero_calibration;

void setup()
{
  //startup delay
  delay(5000);

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
  running();
  int val = find_fire();
  int right_front_PT = front_right();
  int left = read_left();
  int right = read_right();
  int left_front_PT = front_left();

  SerialCom->print("Val: "); SerialCom->println(val);
  SerialCom->println(" ");
  SerialCom->print("right_front_PT is: "); SerialCom->println(right_front_PT);
  SerialCom->print("right is: "); SerialCom->println(right);
  SerialCom->print("left_front_PT is: "); SerialCom->println(left_front_PT);
  SerialCom->print("left is: "); SerialCom->println(left);
  SerialCom->println(" ");
  
}