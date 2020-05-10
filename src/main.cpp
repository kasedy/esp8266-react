#include <ESP8266React.h>
#include <FS.h>

#include "effects.h"
#include "LightStateChangeTracker.h"
#include "LightStateWebSocket.h"

AsyncWebServer *webServer;
ESP8266React *esp8266React;
LightStateChangeTracker *lightControllerService;
LightStateWebSocket *lightStateWebSocket;

void setup() {
#if LOGGING
  Serial.begin(74880, SERIAL_8N1, SERIAL_TX_ONLY);
  Serial.setDebugOutput(true);
#endif 

  webServer = new AsyncWebServer(80);
  esp8266React = new ESP8266React(webServer, &SPIFFS);
  lightControllerService = new LightStateChangeTracker(LED_PINS, EFFECT_LIST);
  lightStateWebSocket = new LightStateWebSocket(lightControllerService, webServer, esp8266React->getSecurityManager());
  SPIFFS.begin();
  esp8266React->begin();
  webServer->begin();
}

void loop() {
  esp8266React->loop();
  lightControllerService->loop();
}
