/*
	
	Matrix_Keyboard.h
	
	@Cetaceaqua
	
*/

#ifndef MATRIX_KEYBOARD_H
#define MATRIX_KEYBOARD_H

class Matrix_Keyboard {
public:
  Matrix_Keyboard();
  int get_key(uint8_t pin);

private:
  const int adc_key_min_values[16] = { 10, 230, 470, 70, 280, 530, 110, 350, 600, 400, 180, 640, 680, 730, 790, 860 };
  const int adc_key_max_values[16] = { 40, 260, 500, 100, 310, 560, 140, 350, 630, 430, 210, 660, 710, 760, 820, 890 };
  // 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, *, #, A, B, C, D
  const int num_keys = 16;
};

Matrix_Keyboard::Matrix_Keyboard() {
}

int Matrix_Keyboard::get_key(uint8_t pin) {
  int adc_value = analogRead(pin);
  for (int i = 0; i < num_keys; i++) {
    if (adc_value > adc_key_min_values[i] && adc_value < adc_key_max_values[i]) {
      return i + 1; // 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
    }
  }
  return 0;
}

#endif  // MATRIX_KEYBOARD_H