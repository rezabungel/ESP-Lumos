#include "web/handlers/PingHandler.h"

void handlePing(AsyncWebServerRequest *request)
{
    request->send(200, "application/json", "{\"status\":\"ok\"}");
}
