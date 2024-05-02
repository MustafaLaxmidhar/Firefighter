// Assign Fan pins
// Decide layout of ALL sensors before full implementation
// Add phototransistor reading function
// rewrite avoid function

# include <Servo.h>   // include the library of servo motor control
// define the control pin of each motor
const byte left_front = 46;
const byte left_rear = 47;
const byte right_rear = 50;
const byte right_front = 51;

float irdist_1, irdist_2, irdist_5, irdist_6;

// define threshold of phototransistor  difference 
int photo_dead_zone = 5;
//  define the sensor reading results 
 int photo_left ;
 int photo_right;
 int photo_three;
 int photo_four;

// USS Setup

float sonar_dist;
float measureSonar();

// three machine states 
enum STATE {
  INITIALISING,
  RUNNING, 
  STOPPED
};

// define motions states 
enum MOTION{
FORWARD,
BACKWARD,
LEFT_TURN,
RIGHT_TURN,
LEFT_ARC,
RIGHT_ARC,
BACKWARD_LEFT_TURN,
STOP
  };
 

// declare function output and function flag   
MOTION cruise_command;
int cruise_output_flag;
MOTION follow_command;
int follow_output_flag;
MOTION extinguish_command;
int extinguish_output_flag;
MOTION avoid_command;
int avoid_output_flag;
MOTION motor_input;

// create servo objects for each motor 
Servo left_front_motor;
Servo left_rear_motor;
Servo right_rear_motor;
Servo right_front_motor;

int speed_val = 100;
int speed_change;

void setup() {
Serial.begin(9600);                                             // start serial communication 
}

void loop() {
  // put your main code here, to run repeatedly:
static STATE machine_state = INITIALISING;     // start from the sate INITIALIING 
switch (machine_state)
{
  case INITIALISING:
     machine_state = initialising();
     break;
  case RUNNING:
     machine_state = running();
     break;
  case STOPPED:
     machine_state = stopped();
     break;
}
}

STATE initialising(){
  enable_motors();                                 // enable motors 
  Serial.println("INITIALISING");        // print the current stage 
  return RUNNING;                               // return to RUNING STATE DIRECTLY 
}

STATE running(){
  //read_serial_command();                      // read command from serial communication 

    speed_change_smooth();                 //function to speed up and slow down smoothly 

  

   

// four function 
cruise(); 
follow(); 
extinguish();
avoid(); 
// select the output command based on the function priority 
arbitrate();
    photo_left = 0; 
    photo_right = 0;
    photo_three = 0;
    photo_four = 0;
    irdist_1 = 0;
    irdist_2 = 0;
    irdist_5 = 0;
    irdist_6 = 0;
    sonar_dist = 0;
    
  return RUNNING;   // return to RUNNING STATE again, it will run the RUNNING    
                   
}                                                            // STATE REPEATLY 


STATE stopped(){
disable_motors();                           // disable the motors
}


void speed_change_smooth()                  // change speed, called in RUNING STATE
{
  speed_val += speed_change;                  // speed value add on speed change 
   if(speed_val > 500)                          // make sure speed change less than 1000
   speed_val = 500;
   speed_change = 0;    //make speed change equals 0 after updating the speed value 
}

// cruise function output command and flag
void cruise()
{
  cruise_command = FORWARD;
  cruise_output_flag=1; 
  }

// follow function output command and flag
void follow()
{ int delta;
  //int left_photo, right_photo, delta;
    //left_photo=analog(1);
   // right_photo=analog(0);
    delta=photo_right - photo_left;
    if (abs(delta)>photo_dead_zone)
      {if (delta>0)
        follow_command=LEFT_TURN;
      else 
        follow_command=RIGHT_TURN;
      follow_output_flag=1;
      }
    else
      follow_output_flag=0;
             
}

// turn on fan until light goes out or for 10 seconds
void extinguish()
{
  extinguish_command = STOP;
}

// avoid function output command and flag 
void avoid()
{int val;
     val=ir_detect;
    //val=ir_detect();
    if (val==1)
      {avoid_output_flag=1;
      avoid_command=BACKWARD;}
    else if (val==2)
      {avoid_output_flag=1;
      avoid_command=RIGHT_ARC;}
    else if (val==3)
      {avoid_output_flag=1;
      avoid_command=LEFT_ARC;}
    else
      {avoid_output_flag=0;}
     
 }

// check flag and select command based on priority 
void arbitrate ()
 {
  if (cruise_output_flag==1)
  {motor_input=cruise_command;}
  if (follow_output_flag==1)
  {motor_input=follow_command;}
  if (extinguish_output_flag ==1)
  {motor_input=extinguish_command;}
  if (avoid_output_flag ==1)
  {motor_input=avoid_command;}
  robotMove();                                    
  }

// connect the selected commands to the robot motions 
void robotMove()
{
switch(motor_input)
{
  case FORWARD:
  forward ();
  delay(1000);
  break;
  
  case BACKWARD:
  reverse ();
  delay(1000);
  break;
  
  case LEFT_TURN:
  ccw();
 delay(1000);
  break;
 
  case RIGHT_TURN:
  cw();
 delay(1000);
  break;
 
  case LEFT_ARC:
  strafe_left();
  delay(1000);
  break;
 
  case RIGHT_ARC:
  strafe_right();
   delay(1000);
  break;

  case BACKWARD_LEFT_TURN:
  reverse_ccw();
  delay(1000);
  break;

  case STOP:
  stop();
  delay(1000);
  }
}

void disable_motors(){                             // function disable all motors, called in  STOPPED STATE
  left_front_motor.detach();
  left_rear_motor.detach();
  right_rear_motor.detach();
  right_front_motor.detach();

  pinMode(left_front,INPUT);                   // set pinMode for next step 
  pinMode(left_rear,INPUT);
  pinMode(right_rear,INPUT);
  pinMode(right_front,INPUT);
}


void enable_motors() {                                //enable all motors, was called in INITIALZING SATE 
  left_front_motor.attach(left_front);
  left_rear_motor.attach(left_rear);
  right_rear_motor.attach(right_rear);
  right_front_motor.attach(right_front);
}

void stop(){                                                                // stop motors 
  left_front_motor.writeMicroseconds(1500);
  left_rear_motor.writeMicroseconds(1500);
  right_rear_motor.writeMicroseconds(1500);
  right_front_motor.writeMicroseconds(1500);
}
void forward(){                                                         // moving forward  
  left_front_motor.writeMicroseconds(1500 + speed_val);
  left_rear_motor.writeMicroseconds(1500 + speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_front_motor.writeMicroseconds(1500 - speed_val);
}

void reverse(){                                                                  // reverse  
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_front_motor.writeMicroseconds(1500 + speed_val);
}
void strafe_left(){                                                         // straight left  
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 + speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_front_motor.writeMicroseconds(1500 - speed_val);
}
void strafe_right(){                                                  //straight right  
  left_front_motor.writeMicroseconds(1500 + speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_front_motor.writeMicroseconds(1500 + speed_val);
}
void cw(){                                                                   //clockwise  
  left_front_motor.writeMicroseconds(1500 + speed_val);
  left_rear_motor.writeMicroseconds(1500 + speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_front_motor.writeMicroseconds(1500 + speed_val);
}
void ccw(){                                                              //anticlockwise  
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_front_motor.writeMicroseconds(1500 - speed_val);
}

void reverse_ccw()
{
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 + speed_val);
  right_front_motor.writeMicroseconds(1500 + speed_val);
  delay(500);
  left_front_motor.writeMicroseconds(1500 - speed_val);
  left_rear_motor.writeMicroseconds(1500 - speed_val);
  right_rear_motor.writeMicroseconds(1500 - speed_val);
  right_front_motor.writeMicroseconds(1500 - speed_val);
}

inline void measure_dist1() {

  float current_mean = 0;
  float previous_mean = 0;
  float next_mean = 0;
  float Sigmat = 0;
  float Sigmat_next = 0;
  float previous_sigma = 0;
  double voltage = 0;

  float Q = 1;
  float R = 0.01;  // values closer to 1 cause faster convergence but less accurate

  float Kt = 0;

  float dist = 0;

  float time1 = millis();
  // Tweak the number of iterations
  for (int i = 0; i < 60; i++) {
    voltage = analogRead(A4);
    dist = 10307 * pow(voltage, -0.847);

    current_mean = previous_mean;
    Sigmat = previous_sigma + R;

    Kt = Sigmat / (Sigmat + Q);
    next_mean = current_mean + Kt * (dist - current_mean);
    Sigmat_next = (1 - Kt * Sigmat);

    previous_sigma = Sigmat_next;
    previous_mean = next_mean;
  }

  float time2 = millis();

  float time = time2 - time1;
  irdist_1 = next_mean;

  if (irdist_1 != irdist_1) {
    irdist_1 = 2000;
  }
}

inline void measure_dist2() {

  float current_mean = 0;
  float previous_mean = 0;
  float next_mean = 0;
  float Sigmat = 0;
  float Sigmat_next = 0;
  float previous_sigma = 0;
  double voltage = 0;

  float Q = 1;
  float R = 0.01;  // values closer to 1 cause faster convergence but less accurate

  float Kt = 0;

  float dist = 0;

  float time1 = millis();
  // Tweak the number of iterations
  for (int i = 0; i < 60; i++) {

    voltage = analogRead(A5);
    dist = 9091.2 * pow(voltage, -0.825);

    current_mean = previous_mean;
    Sigmat = previous_sigma + R;

    Kt = Sigmat / (Sigmat + Q);
    next_mean = current_mean + Kt * (dist - current_mean);
    Sigmat_next = (1 - Kt * Sigmat);

    previous_sigma = Sigmat_next;
    previous_mean = next_mean;
  }

  float time2 = millis();

  float time = time2 - time1;
  irdist_2 = next_mean;

  if (irdist_2 != irdist_2) {
    irdist_2 = 2000;
  }

  // SerialCom->print("Short 2 is: ");
  // SerialCom->println(SHORT_irirdist_2);
}

inline void measure_dist5() {

  float current_mean = 0;
  float previous_mean = 0;
  float next_mean = 0;
  float Sigmat = 0;
  float Sigmat_next = 0;
  float previous_sigma = 0;
  double voltage = 0;

  float Q = 1;
  float R = 0.01;  // values closer to 1 cause faster convergence but less accurate

  float Kt = 0;

  float dist = 0;

  float time1 = millis();
  // Tweak the number of iterations
  for (int i = 0; i < 100; i++) {
    voltage = analogRead(A6);
    dist = 10 * 4302.7 * pow(voltage, -0.934);

    current_mean = previous_mean;
    Sigmat = previous_sigma + R;

    Kt = Sigmat / (Sigmat + Q);
    next_mean = current_mean + Kt * (dist - current_mean);
    Sigmat_next = (1 - Kt * Sigmat);

    previous_sigma = Sigmat_next;
    previous_mean = next_mean;
  }

  float time2 = millis();

  float time = time2 - time1;

  //SerialCom->print("Time to estimate: ");
  //SerialCom->println(time);
  irdist_5 = next_mean - 50;

  // SerialCom->print("Long 5 is: ");
  // SerialCom->println(LONG_irdist_5);
  // SerialCom->println(" ");
}

inline void measure_dist6() {

  float current_mean = 0;
  float previous_mean = 0;
  float next_mean = 0;
  float Sigmat = 0;
  float Sigmat_next = 0;
  float previous_sigma = 0;
  double voltage = 0;

  float Q = 1;
  float R = 0.005;  // values closer to 1 cause faster convergence but less accurate

  float Kt = 0;

  float dist = 0;

  float time1 = millis();

  // Tweak the number of iterations
  for (int i = 0; i < 100; i++) {
    voltage = analogRead(A7);
    dist = 10 * 5049.9 * pow(voltage, -1.006);

    current_mean = previous_mean;
    Sigmat = previous_sigma + R;

    Kt = Sigmat / (Sigmat + Q);
    next_mean = current_mean + Kt * (dist - current_mean);
    Sigmat_next = (1 - Kt * Sigmat);

    previous_sigma = Sigmat_next;
    previous_mean = next_mean;
  }

  float time2 = millis();

  float time = time2 - time1;

  irdist_6 = next_mean;

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
