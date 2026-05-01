#include "web/handlers/RootHandler.h"

void handleRoot(AsyncWebServerRequest *request)
{
    request->send(LittleFS, "/static/index.html", "text/html");
}
