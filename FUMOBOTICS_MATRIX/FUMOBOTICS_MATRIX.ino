/*

  FUMOBOTICS
  MATRIX KEYBOARD

  @Javi_Lacking
  @Cetaceaqua

  TODO: Design a case for the module and re-adjust debounce.

*/

#include <VarSpeedServo.h>
#include "Matrix_Keyboard.h"

#define PIN_ARM_LEFT 3
#define PIN_BOUNCE_LEFT 5
#define PIN_ARM_RIGHT 6
#define PIN_BOUNCE_RIGHT 9

#define PIN_MATRIX_KEYBOARD A1

int current_key = -1;
int last_key = -1;
int control_mode = 0;
int command = 0;

VarSpeedServo arm_left;
VarSpeedServo bounce_left;
VarSpeedServo arm_right;
VarSpeedServo bounce_right;

Matrix_Keyboard matrix_keyboard;

void setup() {
  Serial.begin(9600);

  arm_left.attach(PIN_ARM_LEFT);
  bounce_left.attach(PIN_BOUNCE_LEFT);
  arm_right.attach(PIN_ARM_RIGHT);
  bounce_right.attach(PIN_BOUNCE_RIGHT);

  perform_motion(0, 0, 50, 50, 4, 1000);
}

void loop() {
  current_key = matrix_keyboard.get_key(PIN_MATRIX_KEYBOARD);

  if (current_key != last_key) {
      delay(50); // Debounce
      current_key = matrix_keyboard.get_key(PIN_MATRIX_KEYBOARD);
      if (current_key != last_key) {
        last_key = current_key;
        handle_key_press(current_key);
        command = current_key * 10 + control_mode;
      }
  }

  handle_command(command);
}

void handle_key_press(int key) {
  switch (key) {
    case 13: // A
      if (control_mode != 0) {
        control_mode = 0; // Direct Mode
        perform_motion(100, 0, 50, 50, 5, 250);
      }
      break;
    case 14: // B
      if (control_mode != 1) {
        control_mode = 1; // Gesture Mode
        perform_motion(0, 100, 50, 50, 5, 250);
      }
      break;
  }
}

void handle_command(int command) {
  switch (command) {
    case 0:
      perform_default_motion();
      break;
    case 20: // 2 - Up
      perform_motion(75, 75, 100, 100, 4, 0);
      break;
    case 40: // 4 - Left
      perform_motion(50, 0, 25, 75, 3, 0);
      break;
    case 60: // 6 - Right
      perform_motion(0, 50, 75, 25, 3, 0);
      break;
    case 80: // 8 - Down
      perform_motion(25, 25, 0, 0, 4, 0);
      break;

    case 1:
      perform_default_motion();
      break;
    case 11: // 1
      perform_wave_motion();
      break;
    case 21: // 2
      perform_bounce_motion();
      break;
    case 31: // 3
      perform_vibe_motion();
      break;
    case 41: // 4
      perform_dance_motion();
      break;

    default:
      perform_default_motion();
      break;
  }
}

void perform_default_motion() {
  perform_motion(0, 0, 50, 50, 4, 0);
}

void perform_wave_motion() {
  switch (random(0, 2)) {
    case 0:
      for (int i = 0; i < 4; i++) {
        perform_motion(10, 80, 50, 100, 3, 200);
        perform_motion(10, 40, 50, 100, 3, 200);
      }
      break;

    case 1:
      for (int i = 0; i < 4; i++) {
        perform_motion(80, 10, 100, 50, 3, 200);
        perform_motion(40, 10, 100, 50, 3, 200);
      }
      break;
  }
}

void perform_bounce_motion() {
  perform_motion(0, 0, 100, 100, 5, 100);
  perform_motion(20, 20, 80, 80, 5, 100);
}

void perform_dance_motion() {
  for (int i = 0; i < 2; i++) {
    perform_motion(100, 100, 40, 60, 3, 160);
    perform_motion(70, 70, 50, 50, 3, 160);
    perform_motion(100, 100, 60, 40, 3, 160);
    perform_motion(70, 70, 50, 50, 3, 160);
  }
}

void perform_vibe_motion() {
  perform_motion(25, 25, 50, 50, 2, 250);
  perform_motion(0, 0, 75, 25, 2, 500);
  perform_motion(25, 25, 50, 50, 2, 250);
  perform_motion(0, 0, 25, 75, 2, 500);
}

void perform_motion(float arm_left_percent, float arm_right_percent, float bounce_left_percent, float bounce_right_percent, int speed, int delay_ms) {
  float arm_left_deg = 30 + (arm_left_percent / 100 * 120);
  float arm_right_deg = 150 - (arm_right_percent / 100 * 120);
  float bounce_left_deg = 135 - (bounce_left_percent / 100 * 120);
  float bounce_right_deg = 45 + (bounce_right_percent / 100 * 120);

  arm_left.write(arm_left_deg, speed * 25);
  arm_right.write(arm_right_deg, speed * 25);
  bounce_left.write(bounce_left_deg, speed * 25);
  bounce_right.write(bounce_right_deg, speed * 25);

  delay(delay_ms);
}
