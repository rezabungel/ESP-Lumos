#pragma once
#ifndef _SNAKE_PARAMETERS_H_
#define _SNAKE_PARAMETERS_H_

#include <cstdint>

struct SnakeParameters
{
    uint16_t speed;  // milliseconds between each animation step
    uint16_t length; // number of LEDs in snake
};

#endif // _SNAKE_PARAMETERS_H_
