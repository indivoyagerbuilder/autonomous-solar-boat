#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>
#include <string>

// Build a telemetry message (CSV format) for Rockblock
std::string buildTelemetryMessage();

#endif
