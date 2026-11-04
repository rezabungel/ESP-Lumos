#pragma once
#ifndef _LIGHTS_API_H_
#define _LIGHTS_API_H_

#include <ESPAsyncWebServer.h>
#include "House.h"

class LightsApi
{
public:
    explicit LightsApi(House &house);

    void registerRoutes(AsyncWebServer &server);

private:
    House &house;

    void handleGetLights(AsyncWebServerRequest *request);
};

#endif // _LIGHTS_API_H_
