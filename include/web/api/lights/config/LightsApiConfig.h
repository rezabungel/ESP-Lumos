#pragma once
#ifndef _LIGHTS_API_CONFIG_H
#define _LIGHTS_API_CONFIG_H

namespace LightsApiConfig
{
    constexpr const char *LIGHTS_PATH = "^\\/api\\/v1\\/lights$";
    constexpr const char *LIGHT_BY_ID_PATH = "^\\/api\\/v1\\/lights\\/([^/]+)$";

    constexpr const char *LIGHT_ON_BY_ID_PATH =
        "^\\/api\\/v1\\/lights\\/([^/]+)\\/actions\\/on$";
    constexpr const char *LIGHT_OFF_BY_ID_PATH =
        "^\\/api\\/v1\\/lights\\/([^/]+)\\/actions\\/off$";
}

#endif // _LIGHTS_API_CONFIG_H
