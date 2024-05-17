#include <Arduino.h>
#include <SoftwareSerial.h>
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
  // put your main code here, to run repeatedly:
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