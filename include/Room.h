#pragma once
#ifndef _ROOM_H_
#define _ROOM_H_

#include "LightContainer.h"
#include "config/RoomConfig.h"

class Room : public LightContainer<ROOM_MAX_ELEMENTS>
{
public:
    explicit Room(const char *id, const char *name) : LightContainer<ROOM_MAX_ELEMENTS>(id, name) {}
};

#endif // _ROOM_H_
