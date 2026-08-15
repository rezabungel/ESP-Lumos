#pragma once
#ifndef _LIGHT_CONTAINER_H_
#define _LIGHT_CONTAINER_H_

#include <cstdint>
#include "LightElement.h"

template <uint8_t MAX_ELEMENTS>
class LightContainer : public LightElement
{
public:
    explicit LightContainer(const char *name);

    const char *getName() const override;

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
    const char *const name;
    LightElement *elements[MAX_ELEMENTS];
    uint8_t elementCount;
};

#include "LightContainer.tpp"

#endif // _LIGHT_CONTAINER_H_

// TODO: Implement state snapshot for the light hierarchy.
//
// A Strip owns a LightState, while containers such as Room, LightGroup
// and House contain multiple child elements.
//
// We need a separate representation for the aggregated state of a
// container so that the entire hierarchy can be queried at once,
// e.g. for GET /api/state.
//
// Do not couple this to JSON serialization. The state model and its
// serialization should remain separate.
