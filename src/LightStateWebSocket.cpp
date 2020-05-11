#include "LightStateWebSocket.h"

#include <SecurityManager.h>

static const char *STATE_PARAM PROGMEM = "state";
static const char *BRIGHTNESS_PARAM PROGMEM = "brightness";
static const char *SPEED_PARAM PROGMEM = "speed";
static const char *EFFECT_PARAM PROGMEM = "effect";
static const char *EFFECT_LIST_PARAM PROGMEM = "";

void LightStateWebSocket::serializer(LightController& lightController, JsonObject& json) {
  json[FPSTR(STATE_PARAM)] = lightController.isOn();
  json[FPSTR(BRIGHTNESS_PARAM)] = lightController.getLightBrightness();
  if (lightController.supportsAnimation()) {
    json[FPSTR(SPEED_PARAM)] = lightController.getAnimationSpeed();
    json[FPSTR(EFFECT_PARAM)] = lightController.getCurrentAnimationIndex();
    JsonArray effectOptions = json.createNestedArray(F("effect_list"));
    for (size_t index = 0; index < lightController.getAnimationCount(); ++index) {
      effectOptions.add(lightController.getAnimationName(index));
    }
  }
}

void LightStateWebSocket::deserializer(JsonObject& json, LightController& lightController) {
  lightController.setStateOn(json[FPSTR(STATE_PARAM)] | lightController.isOn());
  lightController.setLightBrightness(json[FPSTR(BRIGHTNESS_PARAM)] | lightController.getLightBrightness());
  if (lightController.supportsAnimation()) {
    lightController.setAnimationSpeed(json[FPSTR(SPEED_PARAM)] | lightController.getAnimationSpeed());
    lightController.setAnimationByIndex(json[FPSTR(EFFECT_PARAM)] | lightController.getCurrentAnimationIndex());
  }
}

LightStateWebSocket::LightStateWebSocket(SettingsService<LightController>* settingsService, 
                                         AsyncWebServer* webServer,
                                         SecurityManager* securityManager) : 
    SettingsSocket<LightController>(serializer, 
                                    deserializer, 
                                    settingsService,
                                    webServer,
                                    "/ws/light",
                                    securityManager,
                                    AuthenticationPredicates::NONE_REQUIRED) {
}