#include "Infrared.h"
#include <Arduino.h>

// IR Sensor Setup
float dist_1, dist_2, dist_5, dist_6;

inline void measure_dist1() {

  float current_mean = 0;
  float previous_mean = 0;
  float next_mean = 0;
  float Sigmat = 0;
  float Sigmat_next = 0;
  float previous_sigma = 0;
  double voltage = 0;

  float Q = 1;
  float R = 0.01;  // values closer to 1 cause faster convergence but less accurate

  float Kt = 0;

  float dist = 0;

  float time1 = millis();
  // Tweak the number of iterations
  for (int i = 0; i < 60; i++) {
    voltage = analogRead(A4);
    dist = 10307 * pow(voltage, -0.847);

    current_mean = previous_mean;
    Sigmat = previous_sigma + R;

    Kt = Sigmat / (Sigmat + Q);
    next_mean = current_mean + Kt * (dist - current_mean);
    Sigmat_next = (1 - Kt * Sigmat);

    previous_sigma = Sigmat_next;
    previous_mean = next_mean;
  }

  float time2 = millis();

  float time = time2 - time1;
  dist_1 = next_mean;

  if (dist_1 != dist_1) {
    dist_1 = 2000;
  }
}

inline void measure_dist2() {

  float current_mean = 0;
  float previous_mean = 0;
  float next_mean = 0;
  float Sigmat = 0;
  float Sigmat_next = 0;
  float previous_sigma = 0;
  double voltage = 0;

  float Q = 1;
  float R = 0.01;  // values closer to 1 cause faster convergence but less accurate

  float Kt = 0;

  float dist = 0;

  float time1 = millis();
  // Tweak the number of iterations
  for (int i = 0; i < 60; i++) {

    voltage = analogRead(A5);
    dist = 9091.2 * pow(voltage, -0.825);

    current_mean = previous_mean;
    Sigmat = previous_sigma + R;

    Kt = Sigmat / (Sigmat + Q);
    next_mean = current_mean + Kt * (dist - current_mean);
    Sigmat_next = (1 - Kt * Sigmat);

    previous_sigma = Sigmat_next;
    previous_mean = next_mean;
  }

  float time2 = millis();

  float time = time2 - time1;
  dist_2 = next_mean;

  if (dist_2 != dist_2) {
    dist_2 = 2000;
  }

  // SerialCom->print("Short 2 is: ");
  // SerialCom->println(SHORT_DIST_2);
}

inline void measure_dist5() {

  float current_mean = 0;
  float previous_mean = 0;
  float next_mean = 0;
  float Sigmat = 0;
  float Sigmat_next = 0;
  float previous_sigma = 0;
  double voltage = 0;

  float Q = 1;
  float R = 0.01;  // values closer to 1 cause faster convergence but less accurate

  float Kt = 0;

  float dist = 0;

  float time1 = millis();
  // Tweak the number of iterations
  for (int i = 0; i < 100; i++) {
    voltage = analogRead(A6);
    dist = 10 * 4302.7 * pow(voltage, -0.934);

    current_mean = previous_mean;
    Sigmat = previous_sigma + R;

    Kt = Sigmat / (Sigmat + Q);
    next_mean = current_mean + Kt * (dist - current_mean);
    Sigmat_next = (1 - Kt * Sigmat);

    previous_sigma = Sigmat_next;
    previous_mean = next_mean;
  }

  float time2 = millis();

  float time = time2 - time1;

  //SerialCom->print("Time to estimate: ");
  //SerialCom->println(time);
  dist_5 = next_mean - 50;

  // SerialCom->print("Long 5 is: ");
  // SerialCom->println(LONG_DIST_5);
  // SerialCom->println(" ");
}

inline void measure_dist6() {

  float current_mean = 0;
  float previous_mean = 0;
  float next_mean = 0;
  float Sigmat = 0;
  float Sigmat_next = 0;
  float previous_sigma = 0;
  double voltage = 0;

  float Q = 1;
  float R = 0.005;  // values closer to 1 cause faster convergence but less accurate

  float Kt = 0;

  float dist = 0;

  float time1 = millis();

  // Tweak the number of iterations
  for (int i = 0; i < 100; i++) {
    voltage = analogRead(A7);
    dist = 10 * 5049.9 * pow(voltage, -1.006);

    current_mean = previous_mean;
    Sigmat = previous_sigma + R;

    Kt = Sigmat / (Sigmat + Q);
    next_mean = current_mean + Kt * (dist - current_mean);
    Sigmat_next = (1 - Kt * Sigmat);

    previous_sigma = Sigmat_next;
    previous_mean = next_mean;
  }

  float time2 = millis();

  float time = time2 - time1;

  dist_6 = next_mean;

}