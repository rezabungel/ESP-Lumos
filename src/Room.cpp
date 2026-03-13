#include "Room.h"

Room::Room() : elementCount(0)
{
}

bool Room::addElement(LightElement *el)
{
    if (!el || elementCount >= MAX_ELEMENTS)
    {
        return false;
    }

    elements[elementCount++] = el;
    return true;
}

void Room::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->setColor(r, g, b);
    }
}

void Room::clear()
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->clear();
    }
}

void Room::setAnimation(Animation *anim)
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->setAnimation(anim);
    }
}
