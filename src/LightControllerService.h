#pragma once

#include <vector>
#include <SettingsService.h>

#include "LightController.h"

class LightControllerService : public SettingsService<LightController> {
public:
  LightControllerService(
    const std::vector<LightController::PinStatus> &pinsGpio, 
    const std::vector<Effect> &effects);

  inline void loop() { _settings.loop(); }
};