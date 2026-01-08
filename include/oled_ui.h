#pragma once
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;
void oled_render_error();
void oled_render_data(float temp, float humid, bool isFahrenheit);
bool olet_init();