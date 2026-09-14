#include "LightElementType.h"

const char *lightElementTypeToString(LightElementType type)
{
    switch (type)
    {
    case LightElementType::House:
        return "house";

    case LightElementType::Room:
        return "room";

    case LightElementType::LightGroup:
        return "lightGroup";

    case LightElementType::Strip:
        return "strip";
    }

    return "unknown";
}
