#include <Arduino.h>
#include "web/api/lights/LightsApi.h"
#include "web/api/lights/config/LightsApiConfig.h"
#include "LightElement.h"
#include "json/JsonBuilder.h"

#if defined(DEBUG_LIGHTS_API) && DEBUG_LIGHTS_API
#define LIGHTS_API_LOG(...) Serial.printf("[LightsApi] " __VA_ARGS__)
#else
#define LIGHTS_API_LOG(...)
#endif

LightsApi::LightsApi(House &house) : house(house)
{
}

void LightsApi::registerRoutes(AsyncWebServer &server)
{
    LIGHTS_API_LOG("Registering routes\n");

    // GET /api/v1/lights
    server.on(
        LightsApiConfig::LIGHTS_PATH,
        HTTP_GET,
        [this](AsyncWebServerRequest *request)
        {
            handleGetLights(request);
        });

    // GET /api/v1/lights/{id}
    server.on(
        LightsApiConfig::LIGHT_BY_ID_PATH,
        HTTP_GET,
        [this](AsyncWebServerRequest *request)
        {
            handleGetLightById(request);
        });

    // POST /api/v1/lights/{id}/actions/on
    server.on(
        LightsApiConfig::LIGHT_ON_BY_ID_PATH,
        HTTP_POST,
        [this](AsyncWebServerRequest *request)
        {
            handlePostLightOnById(request);
        });

    // POST /api/v1/lights/{id}/actions/off
    server.on(
        LightsApiConfig::LIGHT_OFF_BY_ID_PATH,
        HTTP_POST,
        [this](AsyncWebServerRequest *request)
        {
            handlePostLightOffById(request);
        });

    LIGHTS_API_LOG("Routes registered successfully\n");
}

void LightsApi::handleGetLights(AsyncWebServerRequest *request)
{
    LIGHTS_API_LOG("Handling GET %s\n", request->url().c_str());

    JsonBuilder json;

    if (!house.toJson(json))
    {
        LIGHTS_API_LOG("Failed to serialize lights\n");
        request->send(
            500,
            "application/json",
            "{\"error\":\"Failed to serialize lights\"}");
        return;
    }

    LIGHTS_API_LOG("Lights serialized successfully\n");
    request->send(
        200,
        "application/json",
        json.data());
}

void LightsApi::handleGetLightById(AsyncWebServerRequest *request)
{
    LIGHTS_API_LOG("Handling GET %s\n", request->url().c_str());

    const String id = request->pathArg(0);
    LIGHTS_API_LOG("Requested ID: %s\n", id.c_str());

    LightElement *element = house.findElementById(id.c_str());

    if (element == nullptr)
    {
        LIGHTS_API_LOG("Light not found: %s\n", id.c_str());
        request->send(
            404,
            "application/json",
            "{\"error\":\"Light not found\"}");
        return;
    }

    LIGHTS_API_LOG(
        "Found element: id=%s, type=%d\n",
        element->getId(),
        static_cast<int>(element->getType()));

    JsonBuilder json;

    if (!element->toJson(json))
    {
        LIGHTS_API_LOG("Failed to serialize light: %s\n", id.c_str());
        request->send(
            500,
            "application/json",
            "{\"error\":\"Failed to serialize light\"}");
        return;
    }

    LIGHTS_API_LOG("Light serialized successfully: %s\n", id.c_str());
    request->send(
        200,
        "application/json",
        json.data());
}

void LightsApi::handlePostLightOnById(AsyncWebServerRequest *request)
{
    LIGHTS_API_LOG("Handling POST %s\n", request->url().c_str());

    const String id = request->pathArg(0);
    LIGHTS_API_LOG("Requested ID: %s\n", id.c_str());

    LightElement *element = house.findElementById(id.c_str());

    if (element == nullptr)
    {
        LIGHTS_API_LOG("Light not found: %s\n", id.c_str());
        request->send(
            404,
            "application/json",
            "{\"error\":\"Light not found\"}");
        return;
    }

    LIGHTS_API_LOG(
        "Found element: id=%s, type=%d\n",
        element->getId(),
        static_cast<int>(element->getType()));

    element->on();

    LIGHTS_API_LOG("Light turned on: %s\n", id.c_str());
    request->send(204);
}

void LightsApi::handlePostLightOffById(AsyncWebServerRequest *request)
{
    LIGHTS_API_LOG("Handling POST %s\n", request->url().c_str());

    const String id = request->pathArg(0);
    LIGHTS_API_LOG("Requested ID: %s\n", id.c_str());

    LightElement *element = house.findElementById(id.c_str());

    if (element == nullptr)
    {
        LIGHTS_API_LOG("Light not found: %s\n", id.c_str());
        request->send(
            404,
            "application/json",
            "{\"error\":\"Light not found\"}");
        return;
    }

    LIGHTS_API_LOG(
        "Found element: id=%s, type=%d\n",
        element->getId(),
        static_cast<int>(element->getType()));

    element->off();

    LIGHTS_API_LOG("Light turned off: %s\n", id.c_str());
    request->send(204);
}
