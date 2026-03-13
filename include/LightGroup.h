#pragma once
#ifndef _LIGHT_GROUP_H_
#define _LIGHT_GROUP_H_

#include <cstdint>
#include "LightElement.h"
#include "LightGroupConfig.h"

class LightGroup : public LightElement
{
public:
    LightGroup();

    bool addElement(LightElement *el);

    void setColor(uint8_t r, uint8_t g, uint8_t b) override;
    void clear() override;
    void setAnimation(Animation *anim) override;

private:
    static constexpr uint8_t MAX_ELEMENTS = LIGHT_GROUP_MAX_STRIPS;
    LightElement *elements[MAX_ELEMENTS];
    uint8_t elementCount;
};

#endif // _LIGHT_GROUP_H_
