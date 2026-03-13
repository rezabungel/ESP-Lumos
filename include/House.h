#pragma once
#ifndef _HOUSE_H_
#define _HOUSE_H_

#include <cstdint>
#include "LightElement.h"
#include "HouseConfig.h"

class House : public LightElement
{
public:
    House();

    bool addElement(LightElement *el);

    void setColor(uint8_t r, uint8_t g, uint8_t b) override;
    void clear() override;
    void setAnimation(Animation *anim) override;

private:
    static constexpr uint8_t MAX_ELEMENTS = HOUSE_MAX_ELEMENTS;
    LightElement *elements[MAX_ELEMENTS];
    uint8_t elementCount;
};

#endif // _HOUSE_H_
