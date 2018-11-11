#ifndef WiFiScanner_h
#define WiFiScanner_h

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP_PLATFORM)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>
#include <TimeLib.h>

#define SCAN_NETWORKS_SERVICE_PATH "/rest/scanNetworks"
#define LIST_NETWORKS_SERVICE_PATH "/rest/listNetworks"

class WiFiScanner {

  public:

    WiFiScanner(AsyncWebServer *server);

  private:

    AsyncWebServer* _server;

    void scanNetworks(AsyncWebServerRequest *request);
    void listNetworks(AsyncWebServerRequest *request);

};

#endif // end WiFiScanner_h
