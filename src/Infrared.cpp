#include "Infrared.h"
#include <Arduino.h>
#include <math.h>

void ir_setup() {
  // IR Sensors
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);  
  pinMode(A7, INPUT);
}

float measure_dist1() {

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

  dist = next_mean;

  if (dist != dist) {
    dist = 2000;
  }

  return dist;
}

float measure_dist2() {

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

  dist = next_mean;

  if (dist != dist) {
    dist = 2000;
  }

  // SerialCom->print("Short 2 is: ");
  // SerialCom->println(SHORT_DIST_2);

  return dist;
}

float measure_dist5() {

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

  dist = next_mean - 50;

  if (dist != dist) {
    dist = 2000;
  }

  return dist;
}

float measure_dist6() {

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

  dist = next_mean;

  if (dist != dist) {
    dist = 2000;
  }

  return dist;
}


