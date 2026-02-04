#pragma once
#ifndef _SNAKE_ANIMATION_H_
#define _SNAKE_ANIMATION_H_

#include "Animation.h"

class SnakeAnimation : public Animation
{
public:
    SnakeAnimation(uint16_t speed, uint8_t snakeLength);

    bool step(CRGB *leds, uint16_t length, uint32_t now) override;

    void setSpeed(uint16_t s);
    void setSnakeLength(uint8_t l);

private:
    uint16_t speed;      // milliseconds between each animation step
    uint8_t snakeLength; // number of LEDs in snake
    uint16_t head;       // current position of the snake's head
    uint32_t lastUpdate; // timestamp of the last step (from millis())
};

#endif // _SNAKE_ANIMATION_H_
