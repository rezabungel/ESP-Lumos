#include "animation/AnimationType.h"

const char *animationTypeToString(AnimationType type)
{
    switch (type)
    {
    case AnimationType::None:
        return "none";

    case AnimationType::Snake:
        return "snake";

    case AnimationType::Breathing:
        return "breathing";
    }

    return "unknown";
}
