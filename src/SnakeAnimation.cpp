#include "SnakeAnimation.h"

SnakeAnimation::SnakeAnimation(uint16_t speed, uint8_t snakeLength) : speed(speed), snakeLength(snakeLength), head(0), lastUpdate(0)
{
}

void SnakeAnimation::setSpeed(uint16_t s)
{
    speed = s;
}

void SnakeAnimation::setSnakeLength(uint8_t l)
{
    snakeLength = l;
}

bool SnakeAnimation::step(CRGB *leds, uint16_t length, uint32_t now)
{
    if (now - lastUpdate < speed)
    {
        return false;
    }
    lastUpdate = now;

    fill_solid(leds, length, CRGB::Black);

    for (uint8_t i = 0; i < snakeLength; i++)
    {
        uint16_t pos = (head + i) % length;
        leds[pos] = CRGB::Green;
    }

    head = (head + 1) % length;
    return true;
}
