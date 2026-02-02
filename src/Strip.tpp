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
void Strip<PIN>::begin()
{
    FastLED.clear();
}

template <uint8_t PIN>
void Strip<PIN>::on()
{
    fill_solid(leds, length, CRGB::White);
}

template <uint8_t PIN>
void Strip<PIN>::off()
{
    FastLED.clear();
}

template <uint8_t PIN>
void Strip<PIN>::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    fill_solid(leds, length, CRGB(r, g, b));
}
