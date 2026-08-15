#include "animation/snake/SnakeAnimation.h"

SnakeAnimation::SnakeAnimation(const SnakeParameters &parameters) : parameters(parameters), head(0), lastUpdate(0)
{
}

bool SnakeAnimation::step(const LightState &state, CRGB *leds, uint16_t length, uint32_t now)
{
    if (now - lastUpdate < parameters.speed)
    {
        return false;
    }
    lastUpdate = now;

    fill_solid(leds, length, CRGB::Black);

    for (uint16_t i = 0; i < parameters.length; i++)
    {
        uint16_t pos = (head + i) % length;
        leds[pos] = CRGB(state.color.r, state.color.g, state.color.b);
    }

    head = (head + 1) % length;
    return true;
}
