#pragma once
#ifndef _ANIMATION_PARAMETERS_H_
#define _ANIMATION_PARAMETERS_H_

#include <cstdint>
#include "animation/snake/SnakeParameters.h"
#include "animation/breathing/BreathingParameters.h"

union AnimationParameters
{
    SnakeParameters snake;
    BreathingParameters breathing;
};

#endif // _ANIMATION_PARAMETERS_H_
