#pragma once

#include "animations/RandomSplashes.h"

#include <stdint.h>
#include <vector>

class RandomAsynchronousSplashes : public RandomSplashes {
private:
  struct LedInfo {
    uint8_t brightnessSettingsIndex;
    unsigned long timeToChangeBrightness;
  };

  LedInfo *ledInfo;
  void resetTimers(unsigned long timeToChangeBrightness);
  BrightnessSettings nextBrightness(uint8_t index);
public:
  RandomAsynchronousSplashes(
    LightController *lightController, 
    int8_t speed = 0);
  RandomAsynchronousSplashes(
    LightController *lightController, 
    std::vector<BrightnessSettings> brightnessSettings,
    int8_t speed = 0);
  virtual ~RandomAsynchronousSplashes();
  virtual void handle() override;

  static Effect effect(const char* name, int8_t speed = 0);
  static Effect effect(const char* name, std::vector<BrightnessSettings> brightnessSettings, int8_t speed = 0);
};
