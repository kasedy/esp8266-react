#pragma once

#include <vector>
#include <StatefulService.h>
#include <SecurityManager.h>
#include <WebSocketTxRx.h>

#include "LightController.h"

class LightControllerService : public StatefulService<LightController> {
  WebSocketTxRx<LightController> webSocketService;
public:
  LightControllerService(
    const std::vector<LightController::PinStatus> &pinsGpio, 
    const std::vector<Effect> &effects,
    AsyncWebServer* webServer);

  inline void loop() { _state.loop(); }
  inline const LightController& get() const { return _state; }
};