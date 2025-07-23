#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "WiFiConfig.h"
#include "WiFiService.h"
#include "LittleFSService.h"

#define LED_PIN 48
#define NUM_LEDS 10

Adafruit_NeoPixel LED_RGB(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(115200);

  // 1. Init WiFi
  WiFiService wifi;
  if (!wifi.begin(WIFI_SSID, WIFI_PASS))
  {
    Serial.println("Failed to connect to WiFi.");
    ESP.restart();
  }

  // 2.1 Init LittleFS
  LittleFSService little_fs;
  if (!little_fs.begin())
  {
#if LITTLEFS_SHOULD_FORMAT == 0
    Serial.println("Failed to mount LittleFS.");
#elif LITTLEFS_SHOULD_FORMAT == 1
    Serial.println("Failed to format LittleFS.");
#endif
    ESP.restart();
  }

  // 2.2 Verify required paths, directories and files exist in LittleFS
  const char *required_paths[] = {
      "/", "/static", "/static/scripts", "/static/scripts/script.js",
      "/static/styles", "/static/styles/style.css", "/static/index.html"};
  const char *required_dirs[] = {
      "/", "/static", "/static/scripts", "/static/styles"};
  const char *required_files[] = {
      "/static/scripts/script.js", "/static/styles/style.css", "/static/index.html"};
  if (!little_fs.verifyFilesystem(required_paths, sizeof(required_paths) / sizeof(required_paths[0]),
                                  required_dirs, sizeof(required_dirs) / sizeof(required_dirs[0]),
                                  required_files, sizeof(required_files) / sizeof(required_files[0])))
  {
    Serial.println("Error: Filesystem verification failed. Entering deep sleep mode...");
    esp_deep_sleep_start();
  }

  LED_RGB.begin();
  LED_RGB.setBrightness(255);
  LED_RGB.show();
}

void loop()
{
  Serial.println("LED Animation Start");

  for (int i = 0; i < NUM_LEDS; ++i)
  {
    LED_RGB.setPixelColor(i, LED_RGB.Color(0, 255, 0));
  }
  LED_RGB.show();

  for (int i = NUM_LEDS; i > 0; --i)
  {
    LED_RGB.setPixelColor(0, LED_RGB.Color(255, 0, 0));
    LED_RGB.show();

    for (int j = 1; j < i; ++j)
    {
      LED_RGB.setPixelColor(j - 1, LED_RGB.Color(0, 255, 0));
      LED_RGB.setPixelColor(j, LED_RGB.Color(255, 0, 0));
      delay(100);
      LED_RGB.show();
    }
  }

  Serial.println("LED Animation End");
}
