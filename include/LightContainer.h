#pragma once
#ifndef _LIGHT_CONTAINER_H_
#define _LIGHT_CONTAINER_H_

#include <cstdint>
#include "LightElement.h"
#include "json/JsonBuilder.h"

template <uint8_t MAX_ELEMENTS>
class LightContainer : public LightElement
{
public:
    explicit LightContainer(const char *id, const char *name);

    const char *getId() const override;
    const char *getName() const override;

    bool toJson(JsonBuilder &json) const override;

    void setLightState(const LightState &lightState) override;
    void on() override;
    void off() override;
    void setColor(const Color &color) override;
    void setBrightness(uint8_t brightness) override;
    void setAnimationState(const AnimationState &animationState) override;

    LightElement *findElementByPointer(LightElement *searchEl) const;
    LightElement *findElementByName(const char *searchName) const;

    bool addElement(LightElement *el);

protected:
    LightElement *getElement(uint8_t index) const;
    uint8_t getElementCount() const;

private:
    const char *const id;
    const char *const name;
    LightElement *elements[MAX_ELEMENTS];
    uint8_t elementCount;
};

#include "LightContainer.tpp"

#endif // _LIGHT_CONTAINER_H_
