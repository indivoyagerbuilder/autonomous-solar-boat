#include "Telemetry.h"
#include "GPSModule.h"
#include "IMUModule.h"
#include "BatteryMonitor.h"
#include "Autopilot.h"

std::string buildTelemetryMessage() {
  GPSData gps = getGPSData();
  IMUData imu = getIMUData();
  PowerData power = readPowerSensor(SENSOR_BATTERY);

  char buffer[256];
  snprintf(buffer, sizeof(buffer),
           "BOAT1,%lu,%.6f,%.6f,%.1f,%.2f,%.2f,%.2f,%d,%s",
           millis(),
           gps.latitude,
           gps.longitude,
           imu.yaw,
           gps.speed_kmph,
           power.voltage,
           power.current,
           allWaypointsReached() ? -1 : getCurrentWaypointIndex(),
           (gps.valid && imu.valid) ? "NAV" : "WAIT");

  return std::string(buffer);
}
