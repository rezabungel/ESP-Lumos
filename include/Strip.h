#pragma once
#ifndef _STRIP_H_
#define _STRIP_H_

#include <FastLED.h>
#include <cstdint>

#define LED_TYPE WS2815
#define COLOR_ORDER RGB

template <uint8_t PIN>
class Strip
{
public:
    Strip(uint16_t length);
    ~Strip();

    void begin();

    void on();
    void off();
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void update();

private:
    uint16_t length;
    CRGB *leds;
};

#include "Strip.tpp"

#endif // _STRIP_H_
