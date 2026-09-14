#include "LightState.h"

bool LightState::toJson(JsonBuilder &json) const
{
    if (!json.beginObject("state"))
    {
        return false;
    }

    if (!json.add("enabled", enabled))
    {
        return false;
    }

    if (!color.toJson(json))
    {
        return false;
    }

    if (!json.add("brightness", brightness))
    {
        return false;
    }

    if (!animation.toJson(json))
    {
        return false;
    }

    return json.endObject();
}
