#ifndef RC_OVERRIDE_H
#define RC_OVERRIDE_H

#include <Arduino.h>

// Call in setup to initialize RC input
void setupRCOverride();

// Call in loop to update the current RC state
void updateRCOverride();

// Returns true if a valid RC signal is detected
bool isRCOverrideActive();

// Get latest PWM value (1000–2000 µs)
int getRCOverridePWM();

#endif
