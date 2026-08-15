#pragma once
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <FastLED.h>
#include <cstdint>
#include "LightState.h"

class Animation
{
public:
    virtual ~Animation() = default;

    virtual bool step(const LightState &state, CRGB *leds, uint16_t length, uint32_t now) = 0;
};

#endif // _ANIMATION_H_
