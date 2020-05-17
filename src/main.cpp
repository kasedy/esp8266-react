#include <ESP8266React.h>
#include <FS.h>

#include "effects.h"
#include "CapacitiveSensorButtonManager.h"
#include "HomeAssistantMqttBroker.h"
#include "HomeAssistantMqttService.h"
#include "LightControllerService.h"

AsyncWebServer *webServer;
ESP8266React *esp8266React;
LightControllerService *lightControllerService;
HomeAssistantMqttService *homeAssistantMqttService;
HomeAssistantMqttBroker *homeAssistantMqttBroker;
CapacitiveSensorButtonManager *capacitiveSensorButtonManager;

void setup() {
#if LOGGING
  Serial.begin(74880, SERIAL_8N1, SERIAL_TX_ONLY);
  Serial.setDebugOutput(true);
#endif 
  webServer = new AsyncWebServer(80);
  esp8266React = new ESP8266React(webServer, &SPIFFS);
  lightControllerService = new LightControllerService(LED_PINS, EFFECT_LIST, webServer);
  homeAssistantMqttService = new HomeAssistantMqttService(lightControllerService, webServer, &SPIFFS, esp8266React->getSecurityManager());
  homeAssistantMqttBroker = new HomeAssistantMqttBroker(lightControllerService, homeAssistantMqttService, esp8266React->getMqttClient());
  capacitiveSensorButtonManager = new CapacitiveSensorButtonManager(CAPACITIVE_SENSOR_SEND_PIN, CAPACITIVE_SENSOR_RECEIVE_PIN, lightControllerService);

  SPIFFS.begin();
  esp8266React->begin();
  homeAssistantMqttService->begin();
  webServer->begin();
}

void loop() {
  esp8266React->loop();
  capacitiveSensorButtonManager->loop();
  lightControllerService->loop();
}
