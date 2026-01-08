#include <Arduino.h>
#include "app_state.h"
#include "app_config.h"

void button_update() {
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && buttonCurrentState == HIGH) {
    isFahrenheit = !isFahrenheit;
  }

  buttonCurrentState = buttonState;
}
