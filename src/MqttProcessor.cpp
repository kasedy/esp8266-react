#include "MqttProcessor.h"
#include "config.h"
#include "dbg.h"
#include "LightController.h"

#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>
#include <ArduinoJson.h>

const char *CONFIG_MQTT_PAYLOAD_ON PROGMEM = "ON"; 
const char *CONFIG_MQTT_PAYLOAD_OFF PROGMEM = "OFF";

const char *STATE PROGMEM = "state";
const char *BRIGHTNESS PROGMEM = "brightness";
const char *EFFECT PROGMEM = "effect";
const char *WHITE_VALUE PROGMEM = "white_value";

#define MQTT_SERVER "raspberrypi.local"
#define MQTT_PORT 1883

extern LightController *lightController;

namespace MqttProcessor {
  AsyncMqttClient mqttClient;
  Ticker mqttReconnectTimer;

  String getCommandTopic() {
    return String(F("homeassistant/light/")) + DEVICE_SAFE_NAME;
  }

  String getConfigTopic() {
    return getCommandTopic() + F("/config");
  }

  String getStateTopic() {
    return getCommandTopic() + F("/state");
  }

  void connectToMqtt() {
    if (!WiFi.isConnected()) {
      DBG("Trying to connect MQTT but WiFi is not connected!\n");
      mqttReconnectTimer.once(10, connectToMqtt);
    } else if (!mqttClient.connected()) {
      DBG("Connecting to MQTT...\n");
      mqttClient.connect();
    }
  }

  void onMqttConnect(bool sessionPresent) {
    DBG("Connected to MQTT. Session present: %d\n", sessionPresent);
    mqttClient.subscribe(getCommandTopic().c_str(), 1);

    DynamicJsonDocument doc(1024);
    doc[F("schema")] = F("json");
    doc[F("unique_id")] = DEVICE_SAFE_NAME;
    doc[F("name")] = DEVICE_BEAUTIFUL_NAME;
    doc[F("state_topic")] = getStateTopic();
    doc[F("command_topic")] = getCommandTopic();
    doc[F("optimistic")] = false;
    doc[F("qos")] = 2;
    doc[F("retain")] = true;
    doc[FPSTR(BRIGHTNESS)] = true;
    doc[FPSTR(EFFECT)] = lightController->getAnimationCount() > 0;
    doc[FPSTR(WHITE_VALUE)] = true;

    if (lightController->getAnimationCount() > 0) {
      JsonArray effectList = doc.createNestedArray(F("effect_list"));
      for (size_t i = 0; i < lightController->getAnimationCount(); ++i) {
        effectList.add(lightController->getAnimationName(i));
      }
    }
    
    String output;
    serializeJson(doc, output);
    doc.clear();

    DBG("Sending discovery config: %s\n", output.c_str());
    mqttClient.publish(getConfigTopic().c_str(), 2, true, output.c_str(), output.length());
  }

  void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
    DBG("Disconnected from MQTT. Rery in 10 sec. Error code %d\n", reason);
    mqttReconnectTimer.once(10, connectToMqtt);
  }

  void broadcastStateViaMqtt() {
    if (!mqttClient.connected()) {
      DBG("Unable to publish the state to MQTT. Client is not connected.\n");
      return;
    }

    StaticJsonDocument<JSON_OBJECT_SIZE(20)> doc;

    doc[FPSTR(STATE)] = lightController->isOn() ? FPSTR(CONFIG_MQTT_PAYLOAD_ON) : FPSTR(CONFIG_MQTT_PAYLOAD_OFF);
    doc[FPSTR(BRIGHTNESS)] = lightController->getLightBrightness();
    if (lightController->getCurrentAnimationIndex() != -1) {
      doc[FPSTR(EFFECT)] = lightController->getCurrentAnimationName();
    }
    doc[FPSTR(WHITE_VALUE)] = lightController->getAnimationSpeed();

    size_t jsonSize = measureJson(doc);
    char buffer[jsonSize + 1];
    serializeJson(doc, buffer, sizeof(buffer));

    String topic = getStateTopic();
    DBG("Publishing state to %s -> %s\n", topic.c_str(), buffer);
    mqttClient.publish(topic.c_str(), 2, false, buffer, jsonSize);
  }

  void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t length, size_t index, size_t total) {
    DBG("Message arrived [%s]\n", topic);

    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';
    DBG("%s\n", message);
    
    StaticJsonDocument<JSON_OBJECT_SIZE(20)> doc;
    DeserializationError error = deserializeJson(doc, message);

    if (error) {
      DBG("parseObject() failed\n");
      return;
    }

    if (doc.containsKey(FPSTR(STATE))) {
      const char *state = doc[FPSTR(STATE)];
      DBG("State = %s\n", state);
      if (strcmp_P(state, CONFIG_MQTT_PAYLOAD_ON) == 0) {
        DBG("Switching ON\n");
        lightController->setStateOn(true);
      }
      else if (strcmp_P(state, CONFIG_MQTT_PAYLOAD_OFF) == 0) {
        DBG("Switching OFF\n");
        lightController->setStateOn(false);
      }
    }

    if (doc.containsKey(FPSTR(BRIGHTNESS))) {
      lightController->setLightBrightness(doc[FPSTR(BRIGHTNESS)]);
    }

    if (doc.containsKey(FPSTR(EFFECT))) {
      lightController->setAnimationByName(doc[FPSTR(EFFECT)]);
    }

    if (doc.containsKey(FPSTR(WHITE_VALUE))) {
      lightController->setAnimationSpeed(doc[FPSTR(WHITE_VALUE)]);
    }
  }

  void setup() {
    mqttClient
      .onConnect(onMqttConnect)
      .onDisconnect(onMqttDisconnect)
      .onMessage(onMqttMessage)
      .setClientId(DEVICE_SAFE_NAME)
      .setServer(MQTT_SERVER, MQTT_PORT);
    connectToMqtt();
  }
};
