#pragma once
#ifndef _ANIMATION_INSTANCE_H_
#define _ANIMATION_INSTANCE_H_

#include "Animation.h"
#include "AnimationState.h"
#include "AnimationStorage.h"
#include "AnimationFactory.h"

class AnimationInstance
{
public:
    AnimationInstance();

    AnimationType getAnimationType() const;

    bool setAnimationState(const AnimationState &animationState);
    void resetAnimation();

    bool step(const LightState &state, CRGB *leds, uint16_t length, uint32_t now);

private:
    Animation *animation;
    AnimationType animationType;
    AnimationStorage storage;
};

#endif // _ANIMATION_INSTANCE_H_
