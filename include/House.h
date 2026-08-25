#pragma once
#ifndef _HOUSE_H_
#define _HOUSE_H_

#include "LightElementType.h"
#include "LightContainer.h"
#include "config/HouseConfig.h"

class House : public LightContainer<HOUSE_MAX_ELEMENTS>
{
public:
    explicit House(const char *id, const char *name) : LightContainer<HOUSE_MAX_ELEMENTS>(id, name) {}

    LightElementType getType() const override
    {
        return LightElementType::House;
    }
};

#endif // _HOUSE_H_
