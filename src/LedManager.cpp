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

    for (uint8_t i = 0; i < count; i++)
    {
        StripBase *strip = strips[i];

        if (strip->hasAnimation())
        {
            if (strip->stepAnimation(now))
            {
                needShow = true;
            }
        }

        if (strip->needsUpdate())
        {
            needShow = true;
        }
    }

    if (!needShow)
        return;

    FastLED.show();

    for (uint8_t i = 0; i < count; i++)
    {
        strips[i]->resetUpdateFlag();
    }
}
