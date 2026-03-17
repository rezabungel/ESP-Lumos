#pragma once
#ifndef _ROOM_H_
#define _ROOM_H_

#include "LightContainer.h"
#include "RoomConfig.h"

class Room : public LightContainer<ROOM_MAX_ELEMENTS>
{
public:
    explicit Room(const char *name) : LightContainer<ROOM_MAX_ELEMENTS>(name) {}
};

#endif // _ROOM_H_
