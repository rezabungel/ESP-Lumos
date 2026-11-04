#include "web/WebServerService.h"

// handlers
#include "web/handlers/RootHandler.h"
#include "web/handlers/PingHandler.h"

WebServerService::WebServerService(LightsApi &lightsApi) : server(WEB_SERVER_PORT), lightsApi(lightsApi)
{
}

void WebServerService::begin()
{
    Serial.println("[WebServer] Initializing...");

    // Pages
    Serial.println("[WebServer] Registering route: /");
    server.on("/", HTTP_GET, handleRoot);

    // Static files
    Serial.println("[WebServer] Registering static: /static/");
    server.serveStatic("/static/", LittleFS, "/static/");

    // API
    Serial.println("[WebServer] Registering API: /api/ping");
    server.on("/api/ping", HTTP_GET, handlePing);

    Serial.println("[WebServer] Registering Lights API");
    lightsApi.registerRoutes(server);

    // Start server
    server.begin();

    Serial.printf("[WebServer] Started on port %u\n", WEB_SERVER_PORT);
}
