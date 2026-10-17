#pragma once
#ifndef _LIGHT_ELEMENT_H_
#define _LIGHT_ELEMENT_H_

#include <cstdint>
#include "Color.h"
#include "LightState.h"
#include "LightElementType.h"
#include "json/JsonBuilder.h"

template <uint8_t MAX_ELEMENTS>
class LightContainer;

class LightElement
{
public:
    virtual ~LightElement() = default;

    const LightElement *getParent() const;
    LightElement *getParent();
    const char *getId() const;
    const char *getName() const;

    const LightElement *getRoot() const;
    LightElement *getRoot();

    virtual LightElementType getType() const = 0;

    virtual bool toJson(JsonBuilder &json) const = 0;

    virtual void setLightState(const LightState &lightState) = 0;

    virtual void on() = 0;
    virtual void off() = 0;

    virtual void setColor(const Color &color) = 0;
    virtual void setBrightness(uint8_t brightness) = 0;
    virtual void setAnimationState(const AnimationState &animationState) = 0;

    virtual LightElement *findElementByPointer(const LightElement *searchEl);
    virtual const LightElement *findElementById(const char *searchId) const;
    virtual LightElement *findElementById(const char *searchId);

protected:
    explicit LightElement(const char *id, const char *name);

    // Provides child access for LightContainer to traverse the tree and check ID uniqueness in hasUniqueIds().
    virtual LightElement *getElement(uint8_t index) const;
    virtual uint8_t getElementCount() const;

private:
    LightElement *parent = nullptr;
    const char *const id;
    const char *const name;

    void setParent(LightElement *parent);

    template <uint8_t MAX_ELEMENTS>
    friend class LightContainer;
};

#endif // _LIGHT_ELEMENT_H_
