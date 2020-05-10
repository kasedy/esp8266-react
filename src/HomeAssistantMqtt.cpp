#include "HomeAssistantMqtt.h"

static const char *CONFIG_MQTT_PAYLOAD_ON PROGMEM = "ON"; 
static const char *CONFIG_MQTT_PAYLOAD_OFF PROGMEM = "OFF";

static const char *STATE PROGMEM = "state";
static const char *BRIGHTNESS PROGMEM = "brightness";
static const char *EFFECT PROGMEM = "effect";
static const char *WHITE_VALUE PROGMEM = "white_value";


void HomeAssistantMqttSerializer(LightController& lightController, JsonObject& doc) {
  doc[FPSTR(STATE)] = lightController.isOn() ? FPSTR(CONFIG_MQTT_PAYLOAD_ON) : FPSTR(CONFIG_MQTT_PAYLOAD_OFF);
  doc[FPSTR(BRIGHTNESS)] = lightController.getLightBrightness();
  if (lightController.getCurrentAnimationIndex() != -1) {
    doc[FPSTR(EFFECT)] = lightController.getCurrentAnimationName();
  }
  doc[FPSTR(WHITE_VALUE)] = lightController.getAnimationSpeed();
}

void HomeAssistantMqttDeserializer(JsonObject& doc, LightController& lightController) {
  const char *state = doc[FPSTR(STATE)] | "";
  if (strcmp_P(state, CONFIG_MQTT_PAYLOAD_ON) == 0) {
    lightController.setStateOn(true);
  } else if (strcmp_P(state, CONFIG_MQTT_PAYLOAD_OFF) == 0) {
    lightController.setStateOn(false);
  }

  lightController.setLightBrightness(doc[FPSTR(BRIGHTNESS)] | lightController.getLightBrightness());
  lightController.setAnimationSpeed(doc[FPSTR(WHITE_VALUE)] | lightController.getAnimationSpeed());
  if (doc[FPSTR(EFFECT)].is<const char*>()) {
    lightController.setAnimationByName(doc[FPSTR(EFFECT)]);
  }
}