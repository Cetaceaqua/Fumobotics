//Fumobotics Sample Code: Motor Center to 90
//Written 2024-06-01 by Javi_Lacking
//www.thingiverse.com/javilacking
//
//Please tweak and modify the code to best suit your Fumobot, but do so at your own risk!
//Redistribution of this code, including modified versions, is allowed. Please credit me for the base code!
//

#include "Servo.h" //stock arduino servo library

Servo armL; //left arm servo
Servo bounceL; //left "bounce" servo
Servo armR; //right arm servo - the direction of movement is flipped from the left
Servo bounceR; //right "bounce" servo - the direction of movement is flipped from the left

void setup() {

  //default pin attachments on the Arduino board for each servo - you can change them as you see fit, but they MUST be on the PWM pins (3,5,6,9,10,11)
  armL.attach(3);
  bounceL.attach(5);
  armR.attach(6);
  bounceR.attach(9);

}

void loop() {

  //applies a signal to each servo to move it to 90 degrees
  armL.write(90);
  bounceL.write(90);
  armR.write(90);
  bounceR.write(90);
}
