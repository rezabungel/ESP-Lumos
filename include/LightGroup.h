#pragma once
#ifndef _LIGHT_GROUP_H_
#define _LIGHT_GROUP_H_

#include "LightElementType.h"
#include "LightContainer.h"
#include "config/LightGroupConfig.h"

class LightGroup : public LightContainer<LIGHT_GROUP_MAX_STRIPS>
{
public:
    explicit LightGroup(const char *id, const char *name) : LightContainer<LIGHT_GROUP_MAX_STRIPS>(id, name) {}

    LightElementType getType() const override
    {
        return LightElementType::LightGroup;
    }
};

#endif // _LIGHT_GROUP_H_
