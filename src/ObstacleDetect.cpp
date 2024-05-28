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

    float threshold_distance = 100;     //Distance until an object is registered
    float front_dist = 100;

    // Create flags for threshold being breached
    bool front_obstacle = false;
    bool left_obstacle = false;
    bool right_obstacle = false;
    bool side_obstacle = false;

    // Check if sensors detect obstacle
    if (e < front_dist) {
        front_obstacle = true;
    }
    if (b < threshold_distance && (b != 9999)) {
        left_obstacle = true;
    }
    if (a < threshold_distance && (a != 9999)) {
        left_obstacle = true;
    }
    if (c < threshold_distance && (c != 9999)) {
        right_obstacle = true;
    } 
    if (d < threshold_distance && (d != 9999)) {
        right_obstacle = true;
    }
    if (a < threshold_distance && d < threshold_distance) {
        side_obstacle = true;
    }
    if (b < 150 && c < 150){
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

    if (front_obstacle){
        val = 4;
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
    if (a >= 1000 && front_dist < 100) {
        val = 5;  // 'a' is the highest and within range
    }else if (a >= b && a >= c && a >= d) {
        val = 3;  // 'a' is the highest
    } else if (b >= a && b >= c && b >= d) {
        val = 2;  // 'b' is the highest
    } else if (c >= a && c >= b && c >= d) {
        val = 1;  // 'c' is the highest
    } else if (d >= a && d >= b && d >= c) {
        val = 4;  // 'd' is the highest
    }

    // If 'a' is the highest, 'val' remains 3

    return val;
}