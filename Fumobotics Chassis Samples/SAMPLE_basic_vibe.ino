//Fumobotics Sample Code: Basic Motions
//Written 2024-06-01 by Javi_Lacking
//www.thingiverse.com/javilacking
//
//Please tweak and modify the code to best suit your Fumobot, but do so at your own risk!
//Redistribution of this code, including modified versions, is allowed. Please credit me for the base code!
//

#include <VarSpeedServo.h> //updated servo library which allows for multiple speeds. download from here: https://forum.arduino.cc/t/varspeedservo-a-modified-servo-library-with-speed-control/61404

VarSpeedServo armL; //left arm servo
VarSpeedServo bounceL; //left "bounce" servo
VarSpeedServo armR; //right arm servo - the direction of movement is flipped from the left
VarSpeedServo bounceR; //right "bounce" servo - the direction of movement is flipped from the left

void setup() {

//default pin attachments on the Arduino board for each servo - you can change them as you see fit, but they MUST be on the PWM pins (3,5,6,9,10,11)
  armL.attach(3); 
  bounceL.attach(5); 
  armR.attach(6);
  bounceR.attach(9);
}

void loop() {

 //see explanation of the "motion" function for what the numbers inside the function call mean
  motion(25,25,50,50,2,250);
  motion(0,0,75,25,2,500);
  motion(25,25,50,50,2,250);
  motion(0,0,25,75,2,500);
}

//this function is for simplifying adding each individual motion, rather than writing out individual servo position & speed commands
//the function call has 6 values: percentage values for each of the four servos (0-100%), a speed value (1-5, 1 is slowest and 5 is fastest), and a time delay in milliseconds

int motion (float armL_percent, float armR_percent, float bounceL_percent, float bounceR_percent, int speed, int beat_ms){

  //this block of code turns the percentage values given to each servos 
  //into degree values that the servo library can read
  float armL_deg = 30+((armL_percent / 100)*120); //the armL lowest point is 30 degrees (0%) and it's highest is 150 degrees (100%)
  float armR_deg = 150-((armR_percent / 100)*120); //the armR lowest point is 150 degrees (0%) and it's highest is 30 degrees (100%)
  float bounceL_deg = 135-((bounceL_percent/100)*120); //the bounceL lowest point is 135 degrees (0%) and it's highest is 15 degrees (100%)
  float bounceR_deg = 45+((bounceR_percent/100)*120); //the bounceR lowest point is 45 degrees (0%) and it's highest is 165 degrees (100%)
  
  //this block of code applies both the servo degree values and the speed value to a servo library command
  armL.write(int(armL_deg),(speed*25)); 
  armR.write(int(armR_deg),(speed*25)); 
  bounceL.write(int(bounceL_deg),(speed*25)); 
  bounceR.write(int(bounceR_deg),(speed*25)); 

  //this applies the time delay to separate each motion from each other 
  //without a delay, the servos would not move because the function would apply different servo degree values basically at the same time
  //you can input a 0 for the delay to string together motions of differing speeds for each servo, then use a standard delay function at the end
  delay(beat_ms);A
}
