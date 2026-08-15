#include "animation/breathing/BreathingAnimation.h"

BreathingAnimation::BreathingAnimation(const BreathingParameters &parameters) : parameters(parameters), currentBrightness(0), lastUpdate(0)
{
}

bool BreathingAnimation::step(const LightState &state, CRGB *leds, uint16_t length, uint32_t now)
{
    return false;
}
