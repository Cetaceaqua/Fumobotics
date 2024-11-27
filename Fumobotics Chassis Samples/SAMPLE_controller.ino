//Fumobotics Sample Code: Controller
//Written 2024-06-09 by Javi_Lacking
//www.thingiverse.com/javilacking
//
//Please tweak and modify the code to best suit your Fumobot, but do so at your own risk!
//Redistribution of this code, including modified versions, is allowed. Please credit me for the base code!
//

#include <VarSpeedServo.h> //updated servo library which allows for multiple speeds. download from here: https://forum.arduino.cc/t/varspeedservo-a-modified-servo-library-with-speed-control/61404

int fb_pad = 0; //basic variable to receive the analog value of the 5-button pad
int mode = 0; //basic variable to store whether the code is in gesture mode or direct control mode
int command = 0; //basic variable to store the result of the 5b_pad and mode variables in a single variable that will sit in the switch case - more on that later

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

  motion(0,0,50,50,4,1000); //rest position: arms at lowest point, bounce at midpoint, med-low speed, delay of 1 second
}

void loop() {
  if(analogRead(A0)>=1004 && analogRead(A0)<=1024){ //neutral position - no buttons on the pad are being pressed
    fb_pad = 0;
  }
  else if(analogRead(A0)>=0 && analogRead(A0)<=20){ //left button is being pressed
    fb_pad = 10;
  }
  else if(analogRead(A0)>=140 && analogRead(A0)<=160){ //up button is being pressed
    fb_pad = 20;
  }
  else if(analogRead(A0)>=480 && analogRead(A0)<=500){ //right button is being pressed
    fb_pad = 30;
  }
  else if(analogRead(A0)>=290 && analogRead(A0)<=310){ //down button is being pressed
    fb_pad = 40;
  }
  else if(analogRead(A0)>=780 && analogRead(A0)<=800){ //action button is being pressed
    if (mode==0){ //currently in control mode
      mode = 1; //turn to gesture mode
      motion(0,100,50,50,5,250); //lift right arm as a signal into gesture mode
    }
    else if (mode==1){ //currently in gesture mode
      mode = 0; //turn to control mode
      motion(100,0,50,50,5,250); //lift left arm as a signal into control mode
    }
  }

  command = fb_pad + mode; //turns fb_pad and mode into a single "number" that can be processed by the following switch case

  switch(command){
    case 0: //neutral in direct control mode
      motion(0,0,50,50,4,0); //rest position: arms at lowest point, bounce at midpoint, high speed, no delay
      break;

    case 10: //direct control left - lean left
      motion(50,0,25,75,3,0); 
      break;
    
    case 20: //direct control up - lean forward
      motion(75,75,100,100,4,0); 
      break;

    case 30: //direct control right - lean right
      motion(0,50,75,25,3,0); 
      break;
    
    case 40: //direct control down - lean back
      motion(25,25,0,0,4,0); 
      break;

    case 1: //neutral in gesture mode
      motion(0,0,50,50,4,0); //rest position: arms at lowest point, bounce at midpoint, high speed, no delay
      break;

    case 11: //left in gesture mode: random left or right wave
    switch(random(0,2)){
      case 0:
       for(int i=0; i<4; i++){
        motion(10,80,50,100,3,200);
        motion(10,40,50,100,3,200);
       }
      break;
      case 1:
       for(int i=0; i<4; i++){
        motion(80,10,100,50,3,200);
        motion(40,10,100,50,3,200);
       }
      break;
    }
      break;

    case 21: //up in gesture mode: giddy bounce
      motion(0,00,100,100,5,100);
      motion(20,20,80,80,5,100);
      break;
      
    case 31: //right in gesture mode: caramelldansen
      for (int i=0; i<1; i++){
        motion(100,100,40,60,3,160);
        motion(70,70,50,50,3,160);
        motion(100,100,60,40,3,160);
        motion(70,70,50,50,3,160);
      }
      break;

    case 41: //down in gesture mode: vibe
      motion(25,25,50,50,2,250);
      motion(0,0,75,25,2,500);
      motion(25,25,50,50,2,250);
      motion(0,0,25,75,2,500);
      break;
  } 
}

int motion (float armL_percent, float armR_percent, float bounceL_percent, float bounceR_percent, int speed, int beat_ms){

  //this block of code turns the percentage values given to each servos into degree values that the servo library can read
  float armL_deg = 30+(armL_percent/100*120); //the armL lowest point is 30 degrees (0%) and it's highest is 150 degrees (100%)
  float armR_deg = 150-(armR_percent/100*120); //the armR lowest point is 150 degrees (0%) and it's highest is 30 degrees (100%)
  float bounceL_deg = 135-(bounceL_percent/100*120); //the bounceL lowest point is 135 degrees (0%) and it's highest is 15 degrees (100%)
  float bounceR_deg = 45+(bounceR_percent/100*120); //the bounceR lowest point is 45 degrees (0%) and it's highest is 165 degrees (100%)

  //this block of code applies both the servo degree values and the speed value to a servo library command
  armL.write(armL_deg,(speed*25)); 
  armR.write(armR_deg,(speed*25)); 
  bounceL.write(bounceL_deg,(speed*25)); 
  bounceR.write(bounceR_deg,(speed*25)); 

  //this applies the time delay to separate each motion from each other - without a delay, the servos would not move because the function would apply different servo degree values basically at the same time
  delay(beat_ms);
}
