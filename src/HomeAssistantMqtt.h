#pragma once

#include <ArduinoJson.h>

#include "LightController.h"

void HomeAssistantMqttSerializer(LightController& settings, JsonObject& root);
void HomeAssistantMqttDeserializer(JsonObject& root, LightController& settings);