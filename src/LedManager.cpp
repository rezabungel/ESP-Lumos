#include "LedManager.h"

LedManager::LedManager() : count(0)
{
}

bool LedManager::addStrip(StripBase *strip)
{
    if (!strip || count >= MAX_STRIPS)
    {
        return false;
    }

    strips[count++] = strip;
    return true;
}

void LedManager::update(uint32_t now)
{
    bool needShow = false;
    for (uint8_t i = 0; i < count; ++i)
    {
        if (strips[i]->render(now))
        {
            needShow = true;
        }
    }

    if (needShow)
    {
        FastLED.show();
    }
}
