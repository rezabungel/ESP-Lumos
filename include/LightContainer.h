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
    LightElement *findElementByPointer(LightElement *searchEl) const;
    LightElement *findElementByName(const char *searchName) const;

    bool addElement(LightElement *el);

    void setColor(uint8_t r, uint8_t g, uint8_t b) override;
    void clear() override;
    void setAnimation(Animation *anim) override;

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
