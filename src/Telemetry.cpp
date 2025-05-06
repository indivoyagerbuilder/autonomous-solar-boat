#include "Telemetry.h"
#include "GPSModule.h"
#include "IMUModule.h"
#include "BatteryMonitor.h"
#include "Autopilot.h"

std::string buildTelemetryMessage() {
  GPSData gps = getGPSData();
  IMUData imu = getIMUData();
  PowerData power = readPowerSensor(SENSOR_BATTERY);

  // Short, fixed-width compressed format:
  // T:<ms> L:<lat> G:<lon> H:<head> S:<spd> V:<volt> C:<curr> W:<wp> S:<stat>
  char buffer[160];
  snprintf(buffer, sizeof(buffer),
           "T:%lu L:%.5f G:%.5f H:%.1f S:%.1f V:%.2f C:%.2f W:%d S:%s",
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
