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

    bool toJson(JsonBuilder &json) const override;

    void setLightState(const LightState &lightState) override;
    void on() override;
    void off() override;
    void setColor(const Color &color) override;
    void setBrightness(uint8_t brightness) override;
    void setAnimationState(const AnimationState &animationState) override;

    LightElement *findElementByPointer(const LightElement *searchEl) override;
    const LightElement *findElementById(const char *searchId) const override;
    LightElement *findElementById(const char *searchId) override;

    bool addElement(LightElement *el);

protected:
    LightElement *getElement(uint8_t index) const override;
    uint8_t getElementCount() const override;

    bool hasUniqueIds(const LightElement *root, const LightElement *el) const;

private:
    LightElement *elements[MAX_ELEMENTS];
    uint8_t elementCount;
};

#include "LightContainer.tpp"

#endif // _LIGHT_CONTAINER_H_
