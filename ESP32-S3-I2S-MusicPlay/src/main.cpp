#include "Audio.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <WiFi.h>

#define PIN_LED 48

#define I2S_DOUT 18
#define I2S_BCLK 4
#define I2S_LRC 5

long check300ms = 0;
Audio audio;

Adafruit_NeoPixel pixels(1, PIN_LED, NEO_GRB + NEO_KHZ800);
uint32_t colors[] = {0xff0000, 0x00ff00, 0x0000ff,
                     0xffff00, 0x00ffff, 0x000000};
uint8_t colorIndex = 0;

void inline autoConfigWifi() {
  pixels.setPixelColor(0, colors[0]);
  pixels.show();
  Serial.println("Start WiFi Connect!");
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin();
  for (int i = 0; WiFi.status() != WL_CONNECTED && i < 100; i++) {
    delay(100);
  }
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.beginSmartConfig();
    Serial.println("Config WiFi with ESPTouch App!");
    pixels.setPixelColor(0, colors[3]);
    pixels.show();
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
    }
    WiFi.stopSmartConfig();
    WiFi.mode(WIFI_MODE_STA);
  }
  Serial.printf("WiFi Connected: %s\n", WiFi.localIP().toString().c_str());
  pixels.setPixelColor(0, colors[1]);
  pixels.show();
}

void inline initAudioDevice() {
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(20, 1);
  auto url = "http://tspc.bbdj.com/2018/09/2/67950-545936/67950.m3u8";
  audio.connecttohost(url);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello ESP-S3!!");
  pixels.begin();
  pixels.setBrightness(10);
  pixels.clear();
  pixels.show();
  autoConfigWifi();
  initAudioDevice();
}

void loop() {
  audio.loop();
  auto ms = millis();
  if (ms - check300ms > 300) {
    check300ms = ms;
    pixels.setPixelColor(0, colors[colorIndex]);
    pixels.show();
    colorIndex = (colorIndex + 1) % 6;
  }
}

void audio_info(const char *info) {
  Serial.print("info        ");
  Serial.println(info);
}
void audio_id3data(const char *info) {
  Serial.print("id3data     ");
  Serial.println(info);
}
void audio_eof_mp3(const char *info) {
  Serial.print("eof_mp3     ");
  Serial.println(info);
}
void audio_showstation(const char *info) {
  Serial.print("station     ");
  Serial.println(info);
}
void audio_showstreamtitle(const char *info) {
  Serial.print("streamtitle ");
  Serial.println(info);
}
void audio_bitrate(const char *info) {
  Serial.print("bitrate     ");
  Serial.println(info);
}
void audio_commercial(const char *info) { // duration in sec
  Serial.print("commercial  ");
  Serial.println(info);
}
void audio_icyurl(const char *info) { // homepage
  Serial.print("icyurl      ");
  Serial.println(info);
}
void audio_lasthost(const char *info) { // stream URL played
  Serial.print("lasthost    ");
  Serial.println(info);
}
