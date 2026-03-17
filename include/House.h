#pragma once
#ifndef _HOUSE_H_
#define _HOUSE_H_

#include "LightContainer.h"
#include "HouseConfig.h"

class House : public LightContainer<HOUSE_MAX_ELEMENTS>
{
public:
    explicit House(const char *name) : LightContainer<HOUSE_MAX_ELEMENTS>(name) {}
};

#endif // _HOUSE_H_
