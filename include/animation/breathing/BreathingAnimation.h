#pragma once
#ifndef _BREATHING_ANIMATION_H_
#define _BREATHING_ANIMATION_H_

#include "animation/Animation.h"
#include "BreathingParameters.h"

class BreathingAnimation : public Animation
{
public:
    explicit BreathingAnimation(const BreathingParameters &parameters);

    bool step(const LightState &state, CRGB *leds, uint16_t length, uint32_t now) override;

private:
    BreathingParameters parameters;

    uint8_t currentBrightness;
    uint32_t lastUpdate;
};

#endif // _BREATHING_ANIMATION_H_
