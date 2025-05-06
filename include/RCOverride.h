#ifndef RC_OVERRIDE_H
#define RC_OVERRIDE_H

#include <Arduino.h>

// Call in setup() to initialize RC input
void setupRCOverride();

// Call in loop() to update latest values
void updateRCOverride();

// True if valid signals are present
bool isRCOverrideActive();

// Get raw PWM values (1000–2000 µs) for rudder and throttle
int getRCRudderPWM();
int getRCThrottlePWM();

// Get normalized control values: -1 to 1 for rudder, 0 to 1 for throttle
float getRCRudderValue();
float getRCThrottleValue();

#endif