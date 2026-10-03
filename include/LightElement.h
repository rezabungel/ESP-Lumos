#pragma once
#ifndef _LIGHT_ELEMENT_H_
#define _LIGHT_ELEMENT_H_

#include <cstdint>
#include "Color.h"
#include "LightState.h"
#include "LightElementType.h"
#include "json/JsonBuilder.h"

class LightElement
{
public:
    virtual ~LightElement() = default;

    const char *getId() const;
    const char *getName() const;
    virtual LightElementType getType() const = 0;

    virtual bool toJson(JsonBuilder &json) const = 0;

    virtual void setLightState(const LightState &lightState) = 0;

    virtual void on() = 0;
    virtual void off() = 0;

    virtual void setColor(const Color &color) = 0;
    virtual void setBrightness(uint8_t brightness) = 0;
    virtual void setAnimationState(const AnimationState &animationState) = 0;

protected:
    explicit LightElement(const char *id, const char *name);

private:
    const char *const id;
    const char *const name;
};

#endif // _LIGHT_ELEMENT_H_
