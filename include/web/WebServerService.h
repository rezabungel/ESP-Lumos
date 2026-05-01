#pragma once
#ifndef _WEB_SERVER_SERVICE_H_
#define _WEB_SERVER_SERVICE_H_

#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "config/WebServerConfig.h"

class WebServerService
{
public:
    WebServerService();
    void begin();

private:
    AsyncWebServer server;
};

#endif // _WEB_SERVER_SERVICE_H_
