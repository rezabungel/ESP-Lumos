#pragma once
#ifndef _ROOM_H_
#define _ROOM_H_

#include <cstdint>
#include "LightElement.h"
#include "RoomConfig.h"

class Room : public LightElement
{
public:
    Room();

    bool addElement(LightElement *el);

    void setColor(uint8_t r, uint8_t g, uint8_t b) override;
    void clear() override;
    void setAnimation(Animation *anim) override;

private:
    static constexpr uint8_t MAX_ELEMENTS = ROOM_MAX_ELEMENTS;
    LightElement *elements[MAX_ELEMENTS];
    uint8_t elementCount;
};

#endif // _ROOM_H_
