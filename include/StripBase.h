#pragma once
#ifndef _STRIP_BASE_H_
#define _STRIP_BASE_H_

#include <cstdint>

class StripBase
{
public:
    virtual ~StripBase() = default;

    virtual bool render(uint32_t now) = 0;
};

#endif // _STRIP_BASE_H_
