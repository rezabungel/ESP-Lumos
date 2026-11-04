#pragma once
#ifndef _WEB_SERVER_SERVICE_H_
#define _WEB_SERVER_SERVICE_H_

#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "config/WebServerConfig.h"
#include "web/api/lights/LightsApi.h"

class WebServerService
{
public:
    explicit WebServerService(LightsApi &lightsApi);
    void begin();

private:
    AsyncWebServer server;
    LightsApi &lightsApi;
};

#endif // _WEB_SERVER_SERVICE_H_
