#pragma once
#ifndef _STRIP_H_
#define _STRIP_H_

#include <FastLED.h>
#include <cstdint>
#include "StripBase.h"
#include "Animation.h"

#define LED_TYPE WS2815
#define COLOR_ORDER RGB

template <uint8_t PIN>
class Strip : public StripBase
{
public:
    Strip(uint16_t length);
    ~Strip();

    CRGB *data();
    uint16_t size() const;

    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void clear();

    bool needsUpdate() const override;
    void resetUpdateFlag() override;

    void setAnimation(Animation *anim);
    bool stepAnimation(uint32_t now) override;

private:
    uint16_t length;
    CRGB *leds;
    bool dirty = true;

    Animation *animation = nullptr;
};

#include "Strip.tpp"

#endif // _STRIP_H_
