/*

	AD_Keyboard.h
	
	KEYES AD Keyboard Module
	
	Link - https://www.keyestudio.com/products/keyes-ad-keyboard-simulate-five-key-module-analog-button-for-arduino-sensor-expansion-board
	
	@Cetaceaqua
	
*/

#ifndef AD_KEYBOARD_H
#define AD_KEYBOARD_H

class AD_Keyboard {
public:
  AD_Keyboard();
  int get_key(uint8_t pin);

private:
  const int adc_key_values[5] = { 20, 160, 310, 500, 800 };
  // Left, Up, Down, Right, Action
  const int num_keys = 5;
};

AD_Keyboard::AD_Keyboard() {
}

int AD_Keyboard::get_key(uint8_t pin) {
  int adc_value = analogRead(pin);
  for (int i = 0; i < num_keys; i++) {
    if (adc_value >= (adc_key_values[i] - 20) && adc_value <= adc_key_values[i]) {
      return i + 1;
      // 1, 2, 3, 4, 5
    }
  }
  return 0;
}

#endif  // AD_KEYBOARD_H