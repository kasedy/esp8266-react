#include <ESP8266React.h>
#include <FS.h>

#include "effects.h"
#include "lightControllerService.h"

AsyncWebServer server(80);
ESP8266React esp8266React(&server, &SPIFFS);
LightControllerService *lightControllerService;

void setup() {
#if LOGGING
  Serial.begin(74880, SERIAL_8N1, SERIAL_TX_ONLY);
  Serial.setDebugOutput(true);
#endif 

  lightControllerService = new LightControllerService(LED_PINS, EFFECT_LIST);
  SPIFFS.begin();
  esp8266React.begin();
  server.begin();
}

void loop() {
  esp8266React.loop();
  lightControllerService->loop();
}
