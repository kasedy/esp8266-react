#pragma once

#include <SecurityManager.h>
#include <SettingsSocket.h>

#include "LightController.h"

class LightStateWebSocket : public SettingsSocket<LightController> {
  static void serializer(LightController& lightController, JsonObject& doc);
  static void deserializer(JsonObject& doc, LightController& lightController);
public:
  LightStateWebSocket(
    SettingsService<LightController>* settingsService, 
    AsyncWebServer* webServer,
    SecurityManager* securityManager);
};