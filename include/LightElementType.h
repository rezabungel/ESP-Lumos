#pragma once
#ifndef _LIGHT_ELEMENT_TYPE_H_
#define _LIGHT_ELEMENT_TYPE_H_

#include <cstdint>

enum class LightElementType : uint8_t
{
    House,
    Room,
    LightGroup,
    Strip
};

#endif // _LIGHT_ELEMENT_TYPE_H_
