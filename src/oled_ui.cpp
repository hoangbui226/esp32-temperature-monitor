#include "app_state.h"
#include "app_config.h"
#include "temp_converter.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool oled_init() {
  return display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
}

void oled_render_error() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 24);
  display.println("ERROR");
  display.setCursor(0, 52);
  display.println("DHT11 read failed");
  display.display();
}

void oled_render_data(float temp, float humid, bool isFahrenheit) {
  char unit;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 18);
  display.print("Temp: ");

  tempConverter(&temp, &unit, isFahrenheit);
  display.print(temp, 0);
  display.print((char)247);
  display.println(unit);

  display.setCursor(0, 42);
  display.print("Hum: ");
  display.print(humid, 0);
  display.println("%");

  display.display();
}
