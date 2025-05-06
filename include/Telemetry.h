#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>
#include <string>

// Build a compressed telemetry message for Rockblock
std::string buildTelemetryMessage();

#endif
