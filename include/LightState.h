#pragma once
#ifndef _LIGHT_STATE_H_
#define _LIGHT_STATE_H_

#include <cstdint>
#include "Color.h"
#include "animation/AnimationState.h"
#include "json/JsonBuilder.h"

struct LightState
{
    bool enabled = false;
    Color color = {0, 0, 0};
    uint8_t brightness = 255;
    AnimationState animation = {AnimationType::None, {}};

    bool toJson(JsonBuilder &json) const;
};

#endif // _LIGHT_STATE_H_
