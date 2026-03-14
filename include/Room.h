#pragma once
#ifndef _ROOM_H_
#define _ROOM_H_

#include "LightContainer.h"
#include "RoomConfig.h"

class Room : public LightContainer<ROOM_MAX_ELEMENTS>
{
public:
    Room() = default;
};

#endif // _ROOM_H_
