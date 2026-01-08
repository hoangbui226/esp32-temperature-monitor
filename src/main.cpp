#include <Arduino.h>
#include <Wire.h>
#include "app_config.h"
#include "app_state.h"
#include "button_input.h"
#include "dht_sensor.h"
#include "oled_ui.h"
#include "temp_converter.h"

DHT dht(DHTPIN, DHTTYPE);
bool oledOk = false;

bool isFahrenheit = false;
bool buttonCurrentState = HIGH;

void setup() {
  Serial.begin(115200);
  delay(100);

  // Init I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(400000);

  // Init DHT11
  dht.begin();

  // Init OLED
  oledOk = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);

  if (!oledOk) {
    Serial.println("OLED init failed.");
    while (true) {
      delay(1000);
    }
  }

  // Button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  float temp, humid;
  // Update button state
  button_update();

  // Render Oled
  if (!dht_read(&temp, &humid)) {
    oled_render_error();
  } else {
    oled_render_data(temp, humid, isFahrenheit);
    Serial.printf("Temp: %.1f | Hum: %.1f\n", temp, humid);
  }
  delay(100);

}