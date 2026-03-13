#include "LightGroup.h"

LightGroup::LightGroup() : elementCount(0)
{
}

bool LightGroup::addElement(LightElement *el)
{
    if (!el || elementCount >= MAX_ELEMENTS)
    {
        return false;
    }

    elements[elementCount++] = el;
    return true;
}

void LightGroup::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->setColor(r, g, b);
    }
}

void LightGroup::clear()
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->clear();
    }
}

void LightGroup::setAnimation(Animation *anim)
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->setAnimation(anim);
    }
}
