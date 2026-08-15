template <uint8_t PIN>
Strip<PIN>::Strip(const char *name, uint16_t length) : name(name), length(length), leds(new CRGB[length])
{
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
const char *Strip<PIN>::getName() const
{
    return name;
}

template <uint8_t PIN>
const LightState &Strip<PIN>::getLightState() const
{
    return lightState;
}

template <uint8_t PIN>
void Strip<PIN>::setLightState(const LightState &lightState)
{
    if (!animationInstance.setAnimationState(lightState.animation))
    {
        return;
    }

    this->lightState = lightState;
    dirty = true;
}

template <uint8_t PIN>
void Strip<PIN>::on()
{
    lightState.enabled = true;
    dirty = true;
}

template <uint8_t PIN>
void Strip<PIN>::off()
{
    lightState.enabled = false;
    dirty = true;
}

template <uint8_t PIN>
void Strip<PIN>::setColor(const Color &color)
{
    lightState.color = color;
    dirty = true;
}

template <uint8_t PIN>
void Strip<PIN>::setBrightness(uint8_t brightness)
{
    lightState.brightness = brightness;
    dirty = true;
}

template <uint8_t PIN>
void Strip<PIN>::setAnimationState(const AnimationState &animationState)
{
    LightState newLightState = lightState;
    newLightState.animation = animationState;

    setLightState(newLightState);
}

template <uint8_t PIN>
bool Strip<PIN>::render(uint32_t now)
{
    if (!lightState.enabled)
    {
        if (!dirty)
        {
            return false;
        }

        fill_solid(leds, length, CRGB::Black);
        dirty = false;

        return true;
    }

    if (lightState.animation.type == AnimationType::None)
    {
        if (!dirty)
        {
            return false;
        }

        fill_solid(leds, length, CRGB(lightState.color.r, lightState.color.g, lightState.color.b));
        dirty = false;

        return true;
    }

    return animationInstance.step(lightState, leds, length, now);
}
