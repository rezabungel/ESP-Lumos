#pragma once
#ifndef _LIGHT_ELEMENT_H_
#define _LIGHT_ELEMENT_H_

#include <cstdint>
#include "Animation.h"

class LightElement
{
public:
    virtual ~LightElement() = default;

    virtual void setColor(uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void clear() = 0;
    virtual void setAnimation(Animation *anim) = 0;
};

#endif // _LIGHT_ELEMENT_H_
