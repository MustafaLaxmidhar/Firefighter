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

    float threshold_distance = 150;     //Distance until an object is registered

    // Create flags for threshold being breached
    bool front_obstacle = false;
    bool left_obstacle = false;
    bool right_obstacle = false;
    bool side_obstacle = false;

    // Check if sensors detect obstacle
    if (e < threshold_distance) {
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
    if (b < 250 && c < 250){
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
    int right_front_PT = read_back();
    int left = read_left();
    int right = read_right();
    int left_front_PT= read_front();

    // Threshold above ambient room lighting
    int threshold = 100;

    if (abs(left_front_PT - right_front_PT) < 175 && right_front_PT > threshold)  // If front two read similar vals you are aligned
    {
        val = 0;
        return val;
    }
    
    // Align front of robot to fire
    if (left > threshold || left_front_PT > threshold)                  // rotate left
    {
        val = 1;
    }else if (right > threshold || right_front_PT > threshold)           // rotate right
    {
        val = 2;
    }

    return val;
}