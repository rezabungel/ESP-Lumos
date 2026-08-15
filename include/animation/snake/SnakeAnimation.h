#pragma once
#ifndef _SNAKE_ANIMATION_H_
#define _SNAKE_ANIMATION_H_

#include "animation/Animation.h"
#include "SnakeParameters.h"

class SnakeAnimation : public Animation
{
public:
    explicit SnakeAnimation(const SnakeParameters &parameters);

    bool step(const LightState &state, CRGB *leds, uint16_t length, uint32_t now) override;

private:
    SnakeParameters parameters;

    uint16_t head;
    uint32_t lastUpdate;
};

#endif // _SNAKE_ANIMATION_H_
