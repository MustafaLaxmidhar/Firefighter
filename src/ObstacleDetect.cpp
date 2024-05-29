#include "ObstacleDetect.h"
#include "Infrared.h"
#include "Sonar.h"
#include "Phototransistor.h"
#include <stdlib.h>

int obstacle_detect() {

    int val = 0;
    float a = measure_dist6();       // Left 
    float b = measure_dist2();       // Left Diagonal
    float c = measure_dist1();       // Right Diagonal
    float d = measure_dist5();       // Right
    float e = measure_sonar();       // Front
    int f = read_front();           // Front PT

    float diag_threshold = 125;     //Distance until an object is registered
    float front_threshold = 120;
    float side_threshold = 90;

    // Create flags for threshold being breached
    bool front_obstacle = false;
    bool left_obstacle = false;
    bool right_obstacle = false;
    bool side_obstacle = false;

    // Check if sensors detect obstacle
    if (e < front_threshold) {
        front_obstacle = true;
    }
    if (b < diag_threshold && (b != 9999)) {
        left_obstacle = true;
    }
    if (a < side_threshold && (a != 9999)) {
        left_obstacle = true;
    }
    if (c < diag_threshold && (c != 9999)) {
        right_obstacle = true;
    } 
    if (d < side_threshold && (d != 9999)) {
        right_obstacle = true;
    }
    if (a < side_threshold && d < side_threshold) {
        side_obstacle = true;
    }
    if (b < 100 && c < 100){
        front_obstacle = true;
    }

    // Arguments to move right (obstacle on the left)
    if (front_obstacle && a > d) {
        val = 2;
    }
    if (left_obstacle) {
        val = 2;
    }

    // Arguments to move left (obstacle on the right)
    if (front_obstacle && d > a) {
        val = 3;
    }
    if (right_obstacle) {
        val = 3;
    }

    // Argument to move back (boxed in on all sides)
    if (front_obstacle && right_obstacle && left_obstacle && side_obstacle) {
        val = 1;
    }

    if (front_obstacle) {
        val = 4;
    }
    if (f >= 995 && e < 110) {
        val = 7;
    }

    return val;

}

int find_fire() {

    // Read from all phototransistors
    int val  = 0;
    int a = read_front();
    int b = front_right();
    int c = front_left();
    int d = read_back();
    float front_dist = measure_sonar();

    // Compare all values to find the highest
    if (a >= 995 && front_dist < 110) {
        val = 5;  // FRONT is the highest and within range
    } else if (a >= b && a >= c && a >= d) {
        val = 3;  // FRONT is the highest
    } else if (b >= a && b >= c && b >= d) {
        val = 2;  // RIGHT is the highest
    } else if (c >= a && c >= b && c >= d) {
        val = 1;  // LEFT is the highest
    } else if (d >= a && d >= b && d >= c) {
        val = 4;  // BACK is the highest
    } else if (abs(b-c) < 300){
        val = 4; // Check if the left/right PT are sensing similar vals and rotates
    }

    return val;
}

int find_max_light() {

    int val  = 0;
    int a = read_front();
    int b = front_right();
    int c = front_left();

    // Compare a, b, and c to find the highest
    if (a >= b && a >= c) {
        val = 1;  // FRONT is the highest
    } else if (b >= a && b >= c) {
        val = 2;  // RIGHT is the highest
    } else if (c >= a && c >= b) {
        val = 3;  // LEFT is the highest
    }

    return val;
}