#include "LightState.h"

bool LightState::toJson(JsonBuilder &json) const
{
    if (!json.beginObject())
    {
        return false;
    }

    if (!json.add("enabled", enabled))
    {
        return false;
    }

    if (!json.add("color") || !color.toJson(json))
    {
        return false;
    }

    if (!json.add("brightness", brightness))
    {
        return false;
    }

    if (!json.add("animation") || !animation.toJson(json))
    {
        return false;
    }

    return json.endObject();
}
