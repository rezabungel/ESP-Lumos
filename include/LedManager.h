#pragma once
#ifndef _LED_MANAGER_H_
#define _LED_MANAGER_H_

#include <FastLED.h>
#include <cstdint>
#include "StripBase.h"
#include "LedManagerConfig.h"

class LedManager
{
public:
    static constexpr uint8_t MAX_STRIPS = LED_MANAGER_MAX_STRIPS;

    LedManager();

    bool addStrip(StripBase *strip);
    void update(uint32_t now);

private:
    StripBase *strips[MAX_STRIPS];
    uint8_t count;
};

#endif // _LED_MANAGER_H_
