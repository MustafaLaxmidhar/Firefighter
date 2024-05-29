#ifndef MOTION_H
#define MOTION_H

// define motions states
enum MOTION
{
  FORWARD,
  BACKWARD,
  LEFT_TURN,
  RIGHT_TURN,
  LEFT_ARC,
  RIGHT_ARC,
  BACKWARD_LEFT_TURN,
  TURN_AROUND,
  STOP
};

void cruise();
void follow();
void extinguish();
void avoid();

int arbitrate();
void robot_move();

#endif
