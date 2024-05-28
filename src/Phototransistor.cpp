#include "Phototransistor.h"
#include <Arduino.h>

int read_back(){
  return analogRead(A15);
}

int read_front(){
  return analogRead(A14);
}

int front_left(){
  return analogRead(A13);
}

int front_right(){
  return analogRead(A12);
}

