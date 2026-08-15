#pragma once
#ifndef _ANIMATION_FACTORY_H_
#define _ANIMATION_FACTORY_H_

#include "Animation.h"
#include "AnimationState.h"
#include "AnimationStorage.h"

class AnimationFactory
{
public:
    static Animation *create(AnimationStorage &storage, const AnimationState &state);
    static void destroy(Animation *animation, AnimationType type);
};

#endif // _ANIMATION_FACTORY_H_
