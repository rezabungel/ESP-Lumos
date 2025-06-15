#pragma once
#ifndef _WIFI_SERVICE_H_
#define _WIFI_SERVICE_H_

#include <WiFi.h>

#define WIFI_CONNECT_TIMEOUT_MS 60000 // Wi-Fi connection timeout in milliseconds

class WiFiService
{
public:
    bool begin(const char *ssid, const char *pass);
    bool isConnected();
    String getSSID();
    IPAddress getIP();
};

#endif // _WIFI_SERVICE_H_
