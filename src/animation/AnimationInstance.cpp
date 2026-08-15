#include "animation/AnimationInstance.h"

AnimationInstance::AnimationInstance() : animation(nullptr), animationType(AnimationType::None)
{
}

AnimationType AnimationInstance::getAnimationType() const
{
    return animationType;
}

bool AnimationInstance::setAnimationState(const AnimationState &animationState)
{
    resetAnimation();

    if (animationState.type == AnimationType::None)
    {
        return true;
    }

    animation = AnimationFactory::create(storage, animationState);

    if (!animation)
    {
        animationType = AnimationType::None;
        return false;
    }

    animationType = animationState.type;
    return true;
}

void AnimationInstance::resetAnimation()
{
    if (!animation)
    {
        animationType = AnimationType::None;
        return;
    }

    AnimationFactory::destroy(animation, animationType);

    animation = nullptr;
    animationType = AnimationType::None;
}

bool AnimationInstance::step(const LightState &state, CRGB *leds, uint16_t length, uint32_t now)
{
    if (!animation)
    {
        return false;
    }

    return animation->step(state, leds, length, now);
}
