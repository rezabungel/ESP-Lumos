template <uint8_t PIN>
Strip<PIN>::Strip(uint16_t length) : length(length)
{
    leds = new CRGB[length];
    FastLED.addLeds<LED_TYPE, PIN, COLOR_ORDER>(leds, length);
}

template <uint8_t PIN>
Strip<PIN>::~Strip()
{
    delete[] leds;
}

template <uint8_t PIN>
CRGB *Strip<PIN>::data()
{
    return leds;
}

template <uint8_t PIN>
uint16_t Strip<PIN>::size() const
{
    return length;
}

template <uint8_t PIN>
void Strip<PIN>::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    animation = nullptr;
    fill_solid(leds, length, CRGB(r, g, b));
    dirty = true;
}

template <uint8_t PIN>
void Strip<PIN>::clear()
{
    fill_solid(leds, length, CRGB::Black);
    dirty = true;
}

template <uint8_t PIN>
bool Strip<PIN>::needsUpdate() const
{
    return dirty;
}

template <uint8_t PIN>
void Strip<PIN>::resetUpdateFlag()
{
    dirty = false;
}

template <uint8_t PIN>
void Strip<PIN>::setAnimation(Animation *anim)
{
    animation = anim;
    dirty = true;
}

template <uint8_t PIN>
bool Strip<PIN>::hasAnimation() const
{
    return animation != nullptr;
}

template <uint8_t PIN>
bool Strip<PIN>::stepAnimation(uint32_t now)
{
    if (animation)
    {
        bool changed = animation->step(leds, length, now);
        if (changed)
        {
            dirty = true;
        }
        return changed;
    }
    return false;
}
