#pragma once

#include "animations/RandomSplashes.h"

#include <stdint.h>
#include <vector>

class RandomSynchronousSplashes : public RandomSplashes {
private:
  unsigned long timeToChangeBrightness;
  uint8_t brightnessSettingsIndex;

  void resetTimer(unsigned long timeToChangeBrightness);
  BrightnessSettings nextBrightness();
public:
  RandomSynchronousSplashes(
    LightController *lightController,
    int8_t speed = 0);
  RandomSynchronousSplashes(
    LightController *lightController, 
    std::vector<BrightnessSettings> brightnessSettings,
    int8_t speed = 0);
  virtual ~RandomSynchronousSplashes();
  virtual void handle() override;

  static Effect effect(const char* name, int8_t speed = 0);
  static Effect effect(const char* name, std::vector<BrightnessSettings> brightnessSettings, int8_t speed = 0);
};
