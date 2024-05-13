#include "Phototransistor.h"
#include <Arduino.h>

int readLeft(){
  return analogRead(A15);
}

int readRight(){
  return analogRead(A14);
}

int readFront(){
  return analogRead(A13);
}

int readBack(){
  return analogRead(A12);
}

