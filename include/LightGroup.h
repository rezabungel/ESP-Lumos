#pragma once
#ifndef _LIGHT_GROUP_H_
#define _LIGHT_GROUP_H_

#include "LightContainer.h"
#include "LightGroupConfig.h"

class LightGroup : public LightContainer<LIGHT_GROUP_MAX_STRIPS>
{
public:
    explicit LightGroup(const char *name) : LightContainer<LIGHT_GROUP_MAX_STRIPS>(name) {}
};

#endif // _LIGHT_GROUP_H_
