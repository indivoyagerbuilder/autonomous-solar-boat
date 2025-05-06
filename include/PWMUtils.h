#ifndef PWM_UTILS_H
#define PWM_UTILS_H

#include <Arduino.h>

// Converts a pulse width in microseconds (1000–2000) to 16-bit PWM duty cycle
inline uint32_t microsecondsToDuty(int microseconds) {
  return (microseconds * 65535UL) / 20000UL;
}

#endif

