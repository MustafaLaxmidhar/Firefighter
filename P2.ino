// Assign Fan pins
// Decide layout of ALL sensors before full implementation
// Add phototransistor reading function and servo function for extingush
// rewrite avoid function



// define threshold of phototransistor  difference 
int photo_dead_zone = 5;
//  define the sensor reading results 
 int photo_left ;
 int photo_right;
 int photo_three;
 int photo_four;
 
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

