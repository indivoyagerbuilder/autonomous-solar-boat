#include "RCOverride.h"
#include "Config.h"

#define RC_TIMEOUT_MS 1000

volatile int pwmThrottle = 1500;
volatile int pwmRudder = 1500;
volatile unsigned long lastRCUpdate = 0;

void IRAM_ATTR throttleISR() {
  pwmThrottle = pulseIn(RC_THROTTLE_PIN, HIGH, 25000);
  lastRCUpdate = millis();
}

void IRAM_ATTR rudderISR() {
  pwmRudder = pulseIn(RC_RUDDER_PIN, HIGH, 25000);
  lastRCUpdate = millis();
}

void setupRCOverride() {
  pinMode(RC_THROTTLE_PIN, INPUT);
  pinMode(RC_RUDDER_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(RC_THROTTLE_PIN), throttleISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RC_RUDDER_PIN), rudderISR, CHANGE);
}

void updateRCOverride() {
  // nothing needed for now
}

bool isRCOverrideActive() {
  return (millis() - lastRCUpdate < RC_TIMEOUT_MS &&
          pwmThrottle >= 1000 && pwmThrottle <= 2000 &&
          pwmRudder >= 1000 && pwmRudder <= 2000);
}

int getRCThrottlePWM() {
  return pwmThrottle;
}

int getRCRudderPWM() {
  return pwmRudder;
}

float getRCThrottleValue() {
  return constrain((pwmThrottle - 1000) / 1000.0, 0.0, 1.0);
}

float getRCRudderValue() {
  return constrain((pwmRudder - 1500) / 500.0, -1.0, 1.0);
}