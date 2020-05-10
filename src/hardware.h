#pragma once

#if defined(HARDWARE_COINTREAU_BOTTLE)
  #define DEVICE_BEAUTIFUL_NAME "Cointreau Bottle"
  #define LED_PINS {0, 1, 2, 3}
#elif defined(HARDWARE_COINTREAU_BOTTLE_2)
  #define DEVICE_BEAUTIFUL_NAME "Cointreau Bottle 2"
  #define LED_PINS {3, 12, 13, 16}
  #define CAPACITIVE_SENSOR_SEND_PIN 5
  #define CAPACITIVE_SENSOR_RECEIVE_PIN 4
#elif defined(HARDWARE_TEST)
  #define DEVICE_BEAUTIFUL_NAME "dev"
  #define LED_PINS {0, 12, 13, 14, 15, 16}
  #define LOGGING true
  #define CAPACITIVE_SENSOR_SEND_PIN 5
  #define CAPACITIVE_SENSOR_RECEIVE_PIN 4
#elif defined(HARDWARE_KITCHEN_LIGHT)
  #define DEVICE_BEAUTIFUL_NAME "Kitchen Light"
  #define LED_PINS {{0, 2}}
#elif defined(HARDWARE_HANGING_BULBS)
  #define DEVICE_BEAUTIFUL_NAME "Hanging bulbs"
  #define LED_PINS {0}  
#endif

#define LEAD_INDICATOR_PIN 2

const char *getDeviceSafeName();
#define DEVICE_SAFE_NAME getDeviceSafeName()