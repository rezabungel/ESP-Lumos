#pragma once
#ifndef _STRIP_H_
#define _STRIP_H_

#include <FastLED.h>
#include <cstdint>
#include "StripBase.h"
#include "LightElement.h"
#include "LightState.h"
#include "LightElementType.h"
#include "animation/AnimationInstance.h"

#define LED_TYPE WS2815
#define COLOR_ORDER RGB

template <uint8_t PIN>
class Strip : public StripBase, public LightElement
{
public:
    explicit Strip(const char *id, const char *name, uint16_t length);
    ~Strip();

    CRGB *data();
    uint16_t size() const;

    const char *getId() const override;
    const char *getName() const override;
    LightElementType getType() const override;

    const LightState &getLightState() const;
    void setLightState(const LightState &lightState) override;

    void on() override;
    void off() override;

    void setColor(const Color &color) override;
    void setBrightness(uint8_t brightness) override;
    void setAnimationState(const AnimationState &animationState) override;

    bool render(uint32_t now) override;

private:
    const char *const id;
    const char *const name;
    uint16_t length;
    CRGB *leds;

    LightState lightState;
    AnimationInstance animationInstance;

    bool dirty = true;
};

#include "Strip.tpp"

#endif // _STRIP_H_
