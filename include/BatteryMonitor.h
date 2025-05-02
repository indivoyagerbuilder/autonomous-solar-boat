#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <Arduino.h>

enum SensorID {
  SENSOR_BATTERY,
  SENSOR_MOTOR,
  SENSOR_SOLAR
};

// Struct to hold INA260 data
struct PowerData {
  float voltage;   // Volts
  float current;   // Amps
  float power;     // Watts
  bool valid;
};

// Call once in setup to initialize all INA260 sensors
void setupBatteryMonitors();

// Read from a specific sensor by name (not address)
PowerData readPowerSensor(SensorID id);

#endif
