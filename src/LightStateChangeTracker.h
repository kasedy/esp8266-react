#pragma once

#include <vector>
#include <SettingsService.h>

#include "LightController.h"

class LightStateChangeTracker : public SettingsService<LightController> {
public:
  LightStateChangeTracker(
    const std::vector<LightController::PinStatus> &pinsGpio, 
    const std::vector<Effect> &effects);

  inline void loop() { _settings.loop(); }
};