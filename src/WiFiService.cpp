#include "WiFiService.h"

bool WiFiService::begin(const char *ssid, const char *pass)
{
    Serial.printf("Connecting to WiFi network: %s\n", ssid);

    WiFi.begin(ssid, pass);
    Serial.println("Connecting");

    unsigned long start = millis();
    while (!isConnected())
    {
        if (millis() - start > WIFI_CONNECT_TIMEOUT_MS)
        {
            Serial.printf("\nConnection to WiFi network '%s' timed out.\n", ssid);
            return false;
        }
        delay(500);
        Serial.print(".");
    }

    Serial.printf("\nWiFi connected, SSID: %s, IP address: %s\n", getSSID().c_str(), getIP().toString().c_str());

    return true;
}

bool WiFiService::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

String WiFiService::getSSID()
{
    return WiFi.SSID();
}

IPAddress WiFiService::getIP()
{
    return WiFi.localIP();
}
