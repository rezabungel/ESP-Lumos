#include <Arduino.h>
#include "config/WiFiConfig.h"
#include "WiFiService.h"
#include "LittleFSService.h"
#include "web/WebServerService.h"
#include "LedManager.h"
#include "House.h"
#include "Room.h"
#include "LightGroup.h"
#include "Strip.h"
#include "LightState.h"

WebServerService webServer;

// ============================================================
//  LED MANAGER INITIALIZATION
//  Create LED manager instance
// ============================================================
LedManager ledManager;

// ============================================================
//  OBJECTS INITIALIZATION
//  Instantiate all objects: House, Room, LightGroup, Strip
// ============================================================
House myHouse("house", "house");
Room room1("room1", "name-room1");
Room room2("room2", "name-room2");
LightGroup lightGroup1("lightGroup1", "name-lightGroup1");
LightGroup lightGroup2("lightGroup2", "name-lightGroup2");
Strip<46> strip1("strip1", "name-strip1", 300);
Strip<48> strip2("strip2", "name-strip2", 300);

// ============================================================
// TEST STATE
// ============================================================
LightState createSnakeState(uint8_t r, uint8_t g, uint8_t b, uint16_t speed, uint16_t length)
{
  LightState state;

  state.enabled = true;

  state.color = {r, g, b};
  state.brightness = 255;

  state.animation.type = AnimationType::Snake;
  state.animation.parameters.snake.speed = speed;
  state.animation.parameters.snake.length = length;

  return state;
}

LightState createStaticState(uint8_t r, uint8_t g, uint8_t b)
{
  LightState state;

  state.enabled = true;

  state.color = {r, g, b};
  state.brightness = 255;

  state.animation.type = AnimationType::None;

  return state;
}

uint32_t testTimer = 0;
uint8_t testStep = 0;

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

  // 3. Initialize and start HTTP web server
  webServer.begin();

  // ========================================================
  // HOUSE HIERARCHY BUILD
  // Build hierarchy: House -> Room -> LightGroup -> Strip
  // House
  // ├── Room 1
  // │   └── LightGroup 1
  // │       └── Strip 1
  // │
  // └── Room 2
  //     └── LightGroup 2
  //         └── Strip 2
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

  // ========================================================
  // INITIAL STATES
  // ========================================================
  strip1.setLightState(createSnakeState(255, 0, 0, 50, 40));
  strip2.setLightState(createStaticState(0, 0, 255));

  Serial.println("Light system initialized.");
}

void loop()
{
  // Serial.println("loop: before update");

  uint32_t now = millis();
  ledManager.update(now);

  // ========================================================
  // AUTOMATED TESTS
  // ========================================================
  if (now - testTimer < 5000)
  {
    return;
  }
  testTimer = now;

  switch (testStep)
  {
  case 0: // TEST 1 - Change color of static strip
    Serial.println("TEST 1: Change strip2 color to green");
    strip2.setColor({0, 255, 0});
    break;

  case 1: // TEST 2 - Turn strip2 off
    Serial.println("TEST 2: Turn strip2 OFF");
    strip2.off();
    break;

  case 2: // TEST 3 - Turn strip2 on
    Serial.println("TEST 3: Turn strip2 ON");
    strip2.on();
    break;

  case 3: // TEST 4 - Change strip1 animation
  {
    Serial.println("TEST 4: Change strip1 animation");

    AnimationState animationState;
    animationState.type = AnimationType::Snake;
    animationState.parameters.snake.speed = 150;
    animationState.parameters.snake.length = 5;

    strip1.setAnimationState(animationState);
    break;
  }

  case 4: // TEST 5 - Change strip1 color
    Serial.println("TEST 5: Change strip1 color to blue");
    strip1.setColor({0, 0, 255});
    break;

  case 5: // TEST 6 - Turn strip1 off
    Serial.println("TEST 6: Turn strip1 OFF");
    strip1.off();
    break;

  case 6: // TEST 7 - Turn strip1 on
    Serial.println("TEST 7: Turn strip1 ON");
    strip1.on();
    break;

  case 7: // TEST 8 - Switch strip1 to static color
    Serial.println("TEST 8: Disable animation");
    strip1.setAnimationState(AnimationState{AnimationType::None, {}});
    break;

  case 8: // TEST 9 - Change static color
    Serial.println("TEST 9: Change strip1 static color");
    strip1.setColor({255, 255, 255});
    break;

  case 9: // TEST 10 - Turn everything off
    Serial.println("TEST 10: Turn everything OFF");
    strip1.off();
    strip2.off();
    break;

  case 10: // TEST 11 - Turn everything on
    Serial.println("TEST 11: Turn everything ON");
    strip1.on();
    strip2.on();
    break;

  default:
    Serial.println("TEST COMPLETE");
    break;
  }
  ++testStep;

  // Serial.println("loop: after update");
}
