#ifndef MACHINESTATE_H
#define MACHINESTATE_H

// three machine states 
enum STATE {
  INITIALISING,
  RUNNING, 
  STOPPED
};

STATE initialising();
STATE running();
STATE stopped();

#endif