#pragma once

#include "dbg.h"
#include "animations/BaseAnimation.h"

#include <Esp.h>

//TODO: rename into LightState or DeviceState
class LightController {
public:
  struct PinStatus {
    PinStatus(uint8_t gpio) : gpio(1, gpio), brightness(0) {}
    PinStatus(std::initializer_list<uint8_t> gpio) : gpio(gpio), brightness(0) {}
    const std::vector<uint8_t> gpio;
    uint8_t brightness;
  };

private:
  uint8_t brightness;
  uint8_t animationSpeed;
  std::vector<PinStatus> pins;
  const std::vector<Effect> effects;
  BaseAnimation *currentEffect;
  uint8_t currentAnimationIndex;
  bool stateOn:1;

  // Reset every loop() call
  bool brightnessChanged:1;
  bool stateOnChanged:1;
  bool effectChanged:1;
  bool animationSpeedChanged:1; 

  // Reset manualy
  bool dirtyFlag:1;

public:
  LightController(const std::vector<PinStatus> &pinsGpio, const std::vector<Effect> &effects);
  ~LightController();

  void loop();

  // ON-OFF
  bool isOn() const;
  void setStateOn(bool newStateOn);
  void toggleState();

  // Animation
  inline bool supportsAnimation() const { return !effects.empty(); }
  size_t getAnimationCount() const;
  uint8_t getCurrentAnimationIndex();
  const char* getAnimationName(size_t index) const;
  const char* getCurrentAnimationName() const;
  void nextAnimation();
  void setAnimationByIndex(uint8_t animationIndex);
  void setAnimationByName(const char* effectName);

  // Brightness
  void setLightBrightness(uint8_t newMaxBrightness);
  uint8_t getLightBrightness() const;

  // Speed
  void setAnimationSpeed(uint8_t newAnimationSpeed);
  uint8_t getAnimationSpeed() const;

  // GPIO control
  void setPinValue(uint8_t pinIndex, uint8_t brightness);
  void setAllPinValue(uint8_t brightness);
  uint8_t getLedBrightness(uint8_t pinIndex) const;
  uint8_t getLedCount() const;
  
  // Dirty flags that reset every loop() call
  bool isMaxBrightensChanged() const;
  bool isStateOnChanged() const;
  bool isEffectChanged() const;
  bool isAnimationSpeedChanged() const;
  bool isChanged() const {
    return isMaxBrightensChanged() 
        || isStateOnChanged() 
        || isEffectChanged() 
        || isAnimationSpeedChanged();
  }

  // Manual diry flag to track change
  inline void resetDirtyFlag() { dirtyFlag = false; }
  inline bool isDirty() const { return dirtyFlag; }
  inline bool getAndResetDirtyFlag() { 
    bool val = dirtyFlag; 
    dirtyFlag = false; 
    return val; 
  }
};