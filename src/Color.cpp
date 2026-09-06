#include "Color.h"

bool Color::toJson(JsonBuilder &json) const
{
    if (!json.beginObject("color"))
    {
        return false;
    }

    if (!json.add("r", r))
    {
        return false;
    }

    if (!json.add("g", g))
    {
        return false;
    }

    if (!json.add("b", b))
    {
        return false;
    }

    return json.endObject();
}
