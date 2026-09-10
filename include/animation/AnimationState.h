#pragma once
#ifndef _ANIMATION_STATE_H_
#define _ANIMATION_STATE_H_

#include "AnimationType.h"
#include "AnimationParameters.h"
#include "json/JsonBuilder.h"

struct AnimationState
{
    AnimationType type;
    AnimationParameters parameters;

    bool toJson(JsonBuilder &json) const;
};

#endif // _ANIMATION_STATE_H_
