#include "animation/AnimationState.h"

bool AnimationState::toJson(JsonBuilder &json) const
{
    if (!json.beginObject("animation"))
    {
        return false;
    }

    if (!json.add("type", animationTypeToString(type)))
    {
        return false;
    }

    if (!json.beginObject("parameters"))
    {
        return false;
    }

    switch (type)
    {
    case AnimationType::None:
        break;

    case AnimationType::Snake:
        if (!json.add("speed", parameters.snake.speed))
        {
            return false;
        }

        if (!json.add("length", parameters.snake.length))
        {
            return false;
        }
        break;

    case AnimationType::Breathing:
        if (!json.add("speed", parameters.breathing.speed))
        {
            return false;
        }

        if (!json.add("minBrightness", parameters.breathing.minBrightness))
        {
            return false;
        }

        if (!json.add("maxBrightness", parameters.breathing.maxBrightness))
        {
            return false;
        }
        break;
    }

    if (!json.endObject())
    {
        return false;
    }

    return json.endObject();
}
