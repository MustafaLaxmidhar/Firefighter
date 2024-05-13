#include "ObstacleDetect.h"
#include "Infrared.h"
#include "Sonar.h"

int ir_detect() {

float a = measure_dist6();       // Left
float b = measure_dist2();       // Left Diagonal
float c = measure_dist1();       // Right Diagonal
float d = measure_dist5();       // Right
float e = measure_sonar();       // Front

    // Assume a is the smallest initially
    float smallest = a; 
    int val = 2; // Variable holding the smallest value

    if (b < smallest) {
        val = 2;
    }
    if (c < smallest) {
        val = 3;
    }
    if (d < smallest) {
        val = 3;
    }
    if (e < smallest) {
        val = 1;
    }

    return val;

}