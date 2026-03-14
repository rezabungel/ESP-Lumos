#pragma once
#ifndef _LIGHT_GROUP_H_
#define _LIGHT_GROUP_H_

#include "LightContainer.h"
#include "LightGroupConfig.h"

class LightGroup : public LightContainer<LIGHT_GROUP_MAX_STRIPS>
{
public:
    LightGroup() = default;
};

#endif // _LIGHT_GROUP_H_
