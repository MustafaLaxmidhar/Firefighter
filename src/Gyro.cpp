#include <Gyro.h>
#include <Arduino.h>

// Gyro Setup
#define gyro_pin A15
float currentAngle = 0;
float gyroZeroVoltage = 0;
unsigned long T1 = 0;
unsigned long T2 = 0;

float gyro_calibration() {

  int sensorValue = 0;  // read out value of sensor
  float sum = 0;
  gyroZeroVoltage = 0;  // the value of voltage when gyro is zero

  for (int i = 0; i < 100; i++) {  //  read 100 values of voltage when gyro is at still, to calculate the zero-drift
    sensorValue = analogRead(A15);
    sum += sensorValue;
    delay(5);
  }
  gyroZeroVoltage = sum / 100;  // average the sum as the zero drifting

  return gyroZeroVoltage;
}

float measure_gyro() {

  T1 = 0;
  T1 = millis();
  // Reads the gyro angle
  float gyroRate = 0;
  float angularVelocity = 0;
  float gyroSensitivity = 0.007;  // Given in V/deg/s
  float rotationThreshold = 0.5;  // Defines minimum angular velocity before registering angle change due to drifting
  float angleChange = 0;

  // convert the 0-1023 signal to 0-5v
  gyroRate = ((analogRead(gyro_pin) * 5) / 1023);
  //SerialCom->print("gyroRate is: ");
  //SerialCom->println(gyroRate);

  // find the voltage offset the value of voltage when gyro is zero (still)
  gyroRate -= ((gyroZeroVoltage / 1023.0) * 5.0) - 0.49;
  //SerialCom->print("gyroRate after offset removed is: ");
  //SerialCom->println(gyroRate);
  //SerialCom->println(" ");

  // read out voltage divided the gyro sensitivity to calculate the angular velocity

  angularVelocity = gyroRate / gyroSensitivity;
  // SerialCom->print("angularVelocity is: ");
  // SerialCom->println(angularVelocity);
  // SerialCom->println(" ");

  // if the angular velocity is less than the threshold, ignore it
  if (abs(angularVelocity) >= rotationThreshold) {

    unsigned long T3 = T1 - T2;
    // we are running a loop in T. one second will run (1000/T).
    angleChange = angularVelocity / (1000 / T3);
    currentAngle += angleChange;
  }

  // Keep the angle between -180 and 180
  if (currentAngle < -180) {
    currentAngle += 360;
  } else if (currentAngle > 180) {
    currentAngle -= 360;
  }

  T2 = T1;
  delay(10);
  //SerialCom->print("current angle is: ");
  //SerialCom->println(currentAngle);
  return -1 * currentAngle;
}