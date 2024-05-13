#include "Phototransistor.h"
#include <Arduino.h>

int read_left(){
  return analogRead(A15);
}

int read_right(){
  return analogRead(A14);
}

int read_front(){
  return analogRead(A13);
}

int read_back(){
  return analogRead(A12);
}

