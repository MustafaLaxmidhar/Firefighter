#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Sonar.h"
#include "Infrared.h"
#include "Gyro.h"
#include "ServoControl.h"

// Serial Pointer
extern HardwareSerial *SerialCom;

// Gyro zero angle voltage
static float gyro_zero_calibration;

void setup() {
 
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

  //start MSG
  SerialCom->println("Start");
}

void loop() {
  SerialCom->println("YOu are PRINTING");
}