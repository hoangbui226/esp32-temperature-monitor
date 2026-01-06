#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ===================== PINOUT ===================== */
#define DHTPIN 4
#define DHTTYPE  DHT11

#define I2C_SDA  21
#define I2C_SCL  19

#define BUTTON_PIN 23
/* ======================================================= */

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  64
#define OLED_RESET     -1

// OLED I2C address
static const uint8_t OLED_ADDR  = 0x3C;

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  delay(100);

  // Init I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(400000);

  // Init DHT11
  dht.begin();

  // Init OLED
  bool oledOk = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);

  if (!oledOk) {
    Serial.println("OLED init failed.");
    while (true) {
      delay(1000);
    }
  }

  // Splash
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Loading...");
  delay(1500);

  // Button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool isFahrenheit = false;
bool buttonCurrentState = HIGH;

// Converter
void tempDisplay(float *temp, char *unit, bool isfahrenheit) {
    if (isfahrenheit) {
        *temp = *temp * 9.0 / 5.0 + 32.0;
        *unit = 'F';
    } else {
        *unit = 'C';
    }
}
void loop() {
  float humid = dht.readHumidity();
  float temp = dht.readTemperature();
  char unit;

  // Check button state
  bool buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW && buttonCurrentState == HIGH) {
    isFahrenheit = !isFahrenheit;
  }
  buttonCurrentState = buttonState;

  // Render OLED
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  if (isnan(humid) || isnan(temp)) {
    display.setTextSize(2);
    display.setCursor(0, 24);
    display.println("ERROR");
    display.setTextSize(1);
    display.setCursor(0, 52);
    display.println("DHT11 read failed");

  } else {
    // Temperature line
    display.setTextSize(2);
    display.setCursor(0, 18);
    display.print("Temp: ");
    tempDisplay(&temp, &unit, isFahrenheit);
    display.print(temp, 0);
    display.print((char)247); // degree symbol
    display.println(unit);
    // Humidity line
    display.setTextSize(2);
    display.setCursor(0, 42);
    display.print("Hum: ");
    display.print(humid, 0);
    display.println("%");
    Serial.printf("Temp: %.1f C | Hum: %.1f %%\n", temp, humid);
  }

  display.display();
  delay(100);
}