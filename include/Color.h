#pragma once
#ifndef _COLOR_H_
#define _COLOR_H_

#include <cstdint>
#include "json/JsonBuilder.h"

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    bool toJson(JsonBuilder &json) const;
};

#endif // _COLOR_H_
