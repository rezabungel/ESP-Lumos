#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "WiFiConfig.h"
#include "WiFiService.h"
#include "LittleFSService.h"
#include "LedManager.h"
#include "House.h"
#include "Room.h"
#include "LightGroup.h"
#include "Strip.h"
#include "SnakeAnimation.h"

// ============================================================
//  LED MANAGER INITIALIZATION
//  Create LED manager instance
// ============================================================
LedManager ledManager;

// ============================================================
//  OBJECTS INITIALIZATION
//  Instantiate all objects: House, Room, LightGroup, Strip
// ============================================================
House myHouse("myHouse");
Room room1("room1");
Room room2("room2");
LightGroup lightGroup1("lightGroup1");
LightGroup lightGroup2("lightGroup2");
Strip<46> strip1("strip1", 300);
Strip<48> strip2("strip2", 300);

// ---
SnakeAnimation snake1(50, 40);
SnakeAnimation snake2(10, 5);
// ---

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

  // ========================================================
  // HOUSE HIERARCHY BUILD
  // Build hierarchy: House -> Room -> LightGroup -> Strip
  // ========================================================
  myHouse.addElement(&room1);
  myHouse.addElement(&room2);
  room1.addElement(&lightGroup1);
  room2.addElement(&lightGroup2);
  lightGroup1.addElement(&strip1);
  lightGroup2.addElement(&strip2);

  // ========================================================
  // LED MANAGER REGISTRATION
  // Register all strips in LED manager
  // ========================================================
  ledManager.addStrip(&strip1);
  ledManager.addStrip(&strip2);

  // ---
  strip1.setAnimation(&snake1);
  strip2.setAnimation(&snake2);
  // ---
}

void loop()
{
  Serial.println("loop: before update");

  uint32_t now = millis();
  ledManager.update(now);

  Serial.println("loop: after update");
}
