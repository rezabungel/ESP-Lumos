#pragma once
#ifndef _ANIMATION_STATE_H_
#define _ANIMATION_STATE_H_

#include "AnimationType.h"
#include "AnimationParameters.h"

struct AnimationState
{
    AnimationType type;
    AnimationParameters parameters;
};

#endif // _ANIMATION_STATE_H_
