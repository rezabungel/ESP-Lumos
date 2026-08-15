#pragma once
#ifndef _ANIMATION_STORAGE_H_
#define _ANIMATION_STORAGE_H_

#include <cstddef>
#include <cstdint>
#include "animation/snake/SnakeAnimation.h"
#include "animation/breathing/BreathingAnimation.h"

class AnimationStorage
{
public:
    static constexpr size_t SIZE =
        sizeof(SnakeAnimation) > sizeof(BreathingAnimation)
            ? sizeof(SnakeAnimation)
            : sizeof(BreathingAnimation);

    static constexpr size_t ALIGNMENT =
        alignof(SnakeAnimation) > alignof(BreathingAnimation)
            ? alignof(SnakeAnimation)
            : alignof(BreathingAnimation);

    alignas(ALIGNMENT) uint8_t buffer[SIZE];
};

#endif // _ANIMATION_STORAGE_H_
