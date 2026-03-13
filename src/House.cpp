#include "House.h"

House::House() : elementCount(0)
{
}

bool House::addElement(LightElement *el)
{
    if (!el || elementCount >= MAX_ELEMENTS)
    {
        return false;
    }

    elements[elementCount++] = el;
    return true;
}

void House::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->setColor(r, g, b);
    }
}

void House::clear()
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->clear();
    }
}

void House::setAnimation(Animation *anim)
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->setAnimation(anim);
    }
}
