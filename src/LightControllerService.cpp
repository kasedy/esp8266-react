#include "LightControllerService.h"

LightControllerService::LightControllerService(
    const std::vector<LightController::PinStatus> &pinsGpio, 
    const std::vector<Effect> &effects) : 
  SettingsService<LightController>(pinsGpio, effects) {
    
}
