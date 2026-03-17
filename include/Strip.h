#pragma once
#ifndef _STRIP_H_
#define _STRIP_H_

#include <FastLED.h>
#include <cstdint>
#include "StripBase.h"
#include "LightElement.h"
#include "Animation.h"

#define LED_TYPE WS2815
#define COLOR_ORDER RGB

template <uint8_t PIN>
class Strip : public StripBase, public LightElement
{
public:
    explicit Strip(const char *name, uint16_t length);
    ~Strip();

    CRGB *data();
    uint16_t size() const;

    const char *getName() const override;

    void setColor(uint8_t r, uint8_t g, uint8_t b) override;
    void clear() override;

    bool needsUpdate() const override;
    void resetUpdateFlag() override;

    void setAnimation(Animation *anim) override;
    bool hasAnimation() const override;
    bool stepAnimation(uint32_t now) override;

private:
    const char *const name;
    uint16_t length;
    CRGB *leds;
    bool dirty = true;

    Animation *animation = nullptr;
};

#include "Strip.tpp"

#endif // _STRIP_H_
