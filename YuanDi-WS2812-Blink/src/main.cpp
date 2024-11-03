#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define PIN_LED 48

Adafruit_NeoPixel pixels(1, PIN_LED, NEO_GRB + NEO_KHZ800);
uint32_t colors[] = {0xff0000, 0x00ff00, 0x0000ff,
                     0xffff00, 0x00ffff, 0x000000};

void setup() {
  Serial.begin(115200);
  Serial.println("Hello ESP-S3!!");
  pixels.begin();
  pixels.setBrightness(10);
}

void loop() {
  for (auto c : colors) {
    pixels.setPixelColor(0, c);
    pixels.show();
    delay(1000);
  }
}