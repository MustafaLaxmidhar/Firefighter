#include "Sonar.h"
#include <Arduino.h>

// USS Setup
#define TRIG_PIN 48
#define ECHO_PIN 49
float sonar_dist = 0;

void sonar_setup() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}

float measureSonar() {  // returns raw sonar distance

  // Using USS to measure x position
  long startTime = 0;
  long endTime = 0;

jump:
  // Trigger ultrasonic signal
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the time for the signal to return
  while (digitalRead(ECHO_PIN) == LOW) { startTime = micros(); }

  while (digitalRead(ECHO_PIN) == HIGH) { endTime = micros(); }

  // Calculate distance in milliimeters
  float pulseDuration = endTime - startTime;
  sonar_dist = pulseDuration / 5.8;

  delay(1);

  return sonar_dist;
}   