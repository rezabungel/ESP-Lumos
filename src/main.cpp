#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 48
#define NUM_LEDS 1

Adafruit_NeoPixel LED_RGB(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  LED_RGB.begin();
  LED_RGB.show();
}

void loop()
{
  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(255, 255, 255)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(0, 255, 255)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(255, 0, 255)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(255, 255, 0)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(255, 0, 0)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(0, 255, 0)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(0, 0, 255)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(128, 128, 128)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(0, 128, 128)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(128, 0, 128)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(128, 128, 0)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(128, 0, 0)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(0, 128, 0)));
  LED_RGB.show();
  delay(500);

  LED_RGB.setPixelColor(0, uint32_t(LED_RGB.Color(0, 0, 128)));
  LED_RGB.show();
  delay(500);
}
