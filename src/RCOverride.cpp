#include "RCOverride.h"
#include "Config.h"

#define RC_TIMEOUT_MS 1000  // Max time between signals before we consider RC lost

volatile int rcPulseWidth = 1500;    // Default/neutral
volatile unsigned long lastPulseTime = 0;

void IRAM_ATTR rcInterruptHandler() {
  rcPulseWidth = pulseIn(RC_OVERRIDE_PIN, HIGH, 25000); // Max 25 ms wait
  lastPulseTime = millis();
}

void setupRCOverride() {
  pinMode(RC_OVERRIDE_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(RC_OVERRIDE_PIN), rcInterruptHandler, CHANGE);
}

void updateRCOverride() {
  // Not much needed here unless we want to smooth or debounce
}

bool isRCOverrideActive() {
  // Consider active if we received a signal recently and it's in a valid range
  int timeSinceLast = millis() - lastPulseTime;
  return (rcPulseWidth >= 1000 && rcPulseWidth <= 2000 && timeSinceLast < RC_TIMEOUT_MS);
}

int getRCOverridePWM() {
  return rcPulseWidth;
}

