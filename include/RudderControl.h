#ifndef RUDDER_CONTROL_H
#define RUDDER_CONTROL_H

#include <Arduino.h>

// Call once to configure rudder PWM pin and center position
void setupRudder();

// Set rudder position from -1.0 (full left) to 1.0 (full right)
void setRudderPosition(float position);

// Centers the rudder at neutral position (0.0)
void centerRudder();

#endif
