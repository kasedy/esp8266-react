#include <ESP8266React.h>
#include <FS.h>

#include "effects.h"
#include "LightControllerService.h"

AsyncWebServer *webServer;
ESP8266React *esp8266React;
LightControllerService *lightControllerService;

void setup() {
#if LOGGING
  Serial.begin(74880, SERIAL_8N1, SERIAL_TX_ONLY);
  Serial.setDebugOutput(true);
#endif 

  webServer = new AsyncWebServer(80);
  esp8266React = new ESP8266React(webServer, &SPIFFS);
  lightControllerService = new LightControllerService(LED_PINS, EFFECT_LIST, webServer);
  SPIFFS.begin();
  esp8266React->begin();
  webServer->begin();
}

void loop() {
  esp8266React->loop();
  lightControllerService->loop();
}
