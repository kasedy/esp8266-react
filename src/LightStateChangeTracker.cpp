#include "LightStateChangeTracker.h"

LightStateChangeTracker::LightStateChangeTracker(
    const std::vector<LightController::PinStatus> &pinsGpio, 
    const std::vector<Effect> &effects) : 
  SettingsService<LightController>(pinsGpio, effects) {
    
}
