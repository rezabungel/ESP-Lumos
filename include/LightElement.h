#pragma once
#ifndef _LIGHT_ELEMENT_H_
#define _LIGHT_ELEMENT_H_

#include <cstdint>
#include "Color.h"
#include "LightState.h"
#include "LightElementType.h"

class LightElement
{
public:
    virtual ~LightElement() = default;

    virtual const char *getId() const = 0;
    virtual const char *getName() const = 0;
    virtual LightElementType getType() const = 0;

    virtual void setLightState(const LightState &lightState) = 0;

    virtual void on() = 0;
    virtual void off() = 0;

    virtual void setColor(const Color &color) = 0;
    virtual void setBrightness(uint8_t brightness) = 0;
    virtual void setAnimationState(const AnimationState &animationState) = 0;
};

#endif // _LIGHT_ELEMENT_H_
