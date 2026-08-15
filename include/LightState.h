#pragma once
#ifndef _LIGHT_STATE_H_
#define _LIGHT_STATE_H_

#include <cstdint>
#include "Color.h"
#include "animation/AnimationState.h"

struct LightState
{
    bool enabled = false;
    Color color = {0, 0, 0};
    uint8_t brightness = 255;
    AnimationState animation = {AnimationType::None, {}};
};

#endif // _LIGHT_STATE_H_
