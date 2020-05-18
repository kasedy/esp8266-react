#ifndef JsonDeserializer_h
#define JsonDeserializer_h

#include <ArduinoJson.h>

/**
 * May return false to prevent unnecessary update propagation in case if 
 * settings object was not changed.
*/
template <class T>
using JsonDeserializer = bool (*)(JsonObject& root, T& settings);

#endif  // end JsonDeserializer
