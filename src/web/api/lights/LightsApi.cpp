#include "web/api/lights/LightsApi.h"
#include "web/api/lights/config/LightsApiConfig.h"
#include "json/JsonBuilder.h"

LightsApi::LightsApi(House &house) : house(house)
{
}

void LightsApi::registerRoutes(AsyncWebServer &server)
{
    server.on(
        LightsApiConfig::LIGHTS_PATH,
        HTTP_GET,
        [this](AsyncWebServerRequest *request)
        {
            handleGetLights(request);
        });
}

void LightsApi::handleGetLights(AsyncWebServerRequest *request)
{
    JsonBuilder json;

    if (!house.toJson(json))
    {
        request->send(
            500,
            "application/json",
            "{\"error\":\"Failed to serialize lights\"}");

        return;
    }

    request->send(200, "application/json", json.data());
}