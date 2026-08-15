#include "animation/AnimationFactory.h"

Animation *AnimationFactory::create(AnimationStorage &storage, const AnimationState &state)
{
    switch (state.type)
    {
    case AnimationType::Snake:
        return new (&storage.buffer)
            SnakeAnimation(state.parameters.snake);

    case AnimationType::Breathing:
        return new (&storage.buffer)
            BreathingAnimation(state.parameters.breathing);

    case AnimationType::None:
        return nullptr;
    }

    return nullptr;
}

void AnimationFactory::destroy(Animation *animation, AnimationType type)
{
    if (!animation)
    {
        return;
    }

    switch (type)
    {
    case AnimationType::Snake:
        static_cast<SnakeAnimation *>(animation)->~SnakeAnimation();
        break;

    case AnimationType::Breathing:
        static_cast<BreathingAnimation *>(animation)->~BreathingAnimation();
        break;

    case AnimationType::None:
        break;
    }
}
