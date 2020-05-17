#include "CapacitiveSensorButton.h"

#include <CapacitiveSensor.h>

#include "dbg.h"

#define NUM_SAMPLES 50
#define PROCESSING_INTERVAL 25
#define THRESHOLD 350
#define CLICK_TIME_THRESHOLD 500
#define DOUBLE_CLICK_TIME_THRESHOLD 250

#define DBG_INFO(fmt, ...)

CapacitiveSensorButton::CapacitiveSensorButton(uint8_t sendPin, uint8_t receivePin, Handler handler) : 
    cs(sendPin, receivePin),
    handler(handler),
    lastAverageCalculation(0),
    lastDownTime(0),
    lastUpTime(0),
    rapidClickCounter(1),
    isPressed(false),
    startHandlingLongPress(false) {
  cs.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs.set_CS_Timeout_Millis(20);
}

void CapacitiveSensorButton::loop() {
  if (!handler) {
    return;
  }

  long sensorTime = cs.capacitiveSensor(NUM_SAMPLES);
  if (sensorTime < 0) {
    DBG("Failed to read capacitive sensor. Error code = %ld\n", sensorTime);
    return;
  }
  touchSensorData.addMeasurement(sensorTime);
  debugTouchSensorData.addMeasurement(sensorTime);

  uint32_t now = millis();
  if (now - lastDebug >= 200) {
    DBG_INFO("min: %-4d avg: %-4d max: %-4d\n", 
        debugTouchSensorData.minValue, 
        debugTouchSensorData.getAverage(), 
        debugTouchSensorData.maxValue);
    debugTouchSensorData.reset();
    lastDebug = now;
  }

  if (now - lastAverageCalculation >= PROCESSING_INTERVAL) {
    if (touchSensorData.getCounter() == 0) {
      DBG_INFO("Failed to get average for capacitive sensor charge time\n");
      return;
    }

    uint32_t averageSensorTime = touchSensorData.getAverage();
    if (isPressed && averageSensorTime < THRESHOLD) {
      isPressed = false;
      startHandlingLongPress = false;
      if (now - lastDownTime > CLICK_TIME_THRESHOLD) {
        rapidClickCounter = 0;
      } else {
        ++rapidClickCounter;
      }
      lastUpTime = now;
      DBG("Touch up %d\n", rapidClickCounter);
    } else if (!isPressed && averageSensorTime > THRESHOLD) {
      isPressed = true;
      startHandlingLongPress = true;
      lastDownTime = now;
      DBG("Touch down\n");
    }

    touchSensorData.reset();
    lastAverageCalculation = now;
  }

  if (!isPressed && now - lastUpTime > DOUBLE_CLICK_TIME_THRESHOLD) {
    handler(rapidClickCounter, EventType::Click);
  }

  if (isPressed && now - lastDownTime > CLICK_TIME_THRESHOLD) {
    DBG("Long press %d\n", rapidClickCounter);
    handler(rapidClickCounter, startHandlingLongPress ? EventType::HoldStart : EventType::Holding);
    startHandlingLongPress = false;
  }
}