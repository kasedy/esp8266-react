#pragma once

#include <vector>
#include <animations/all.h>

Effect noAnimation() {
  return NoAnimation::effect("No animation");
}

Effect effectFadeOnSwitch() {
  return FadeSwitch::effect("Fade on switch");
}

Effect effectFadeInCycle() {
  return FadeCycle::effect("Fade in cycle");
}

Effect effectFadeSingleLed() {
  return SingleLedFade::effect("Fade single led", 255);
}

Effect effectRandomSplashes() {
  return RandomAsynchronousSplashes::effect("Random splashes");
}

Effect effectRandomCompensatedSplashes() {
  return RandomSplashesCompensated::effect("Random compensated splashes");
}

Effect effectRandomBlinks() {
  return RandomAsynchronousSplashes::effect("Random blinks", {{0, 0}, {255, 255}});
}

Effect effectAsycFire() {
  return RandomAsynchronousSplashes::effect("Async fire", {{51, 255}});
}

Effect effectAsycFlame() {
  return RandomAsynchronousSplashes::effect("Async flame", {{25, 255}, {51, 255}, {76, 255}, {102, 255}, {127, 255}, {51, 255}, {153, 255}, {178, 255}, {204, 255}}, 10);
}

Effect effectSyncFire() {
  return RandomSynchronousSplashes::effect("Sync fire", {{51, 255}});
}

Effect effectSyncFlame() {
  return RandomSynchronousSplashes::effect("Sync flame", {{25, 255}, {51, 255}, {76, 255}, {102, 255}, {127, 255}, {51, 255}, {153, 255}, {178, 255}, {204, 255}}, 10);
}

std::vector<Effect> allEffects() {
  return std::vector<Effect>({
    noAnimation(),
    effectRandomCompensatedSplashes(),
    effectFadeOnSwitch(),
    effectFadeSingleLed(),
    effectFadeInCycle(),
    effectRandomSplashes(),
    effectRandomBlinks(),
    effectAsycFire(),
    effectAsycFlame(),
    effectSyncFire(),
    effectSyncFlame(),
  });
}

std::vector<Effect> defaultEffects() {
  return std::vector<Effect>({
    effectRandomCompensatedSplashes(),
    effectFadeOnSwitch(),
    effectFadeSingleLed(),
  });
}

#define EFFECT_LIST (allEffects())