#include "hardware.h"
#include <helpers.h>

const char *getDeviceSafeName() {
  static const char* deviceSafeName = nullptr;
  if (deviceSafeName == nullptr) {
    deviceSafeName = makeSafeName(DEVICE_BEAUTIFUL_NAME);
  }
  return deviceSafeName;
}
