#include "Autopilot.h"
#include "GPSModule.h"
#include "IMUModule.h"
#include "MotorControl.h"
#include "RudderControl.h"

#define WAYPOINT_TOLERANCE_METERS 15.0
#define MOTOR_CRUISE_POWER        0.4

// Hardcoded waypoints
static Waypoint waypoints[] = {
  { -31.9505, 115.8605, false },
  { -32.1, 116.0, false }
};

static const int NUM_WAYPOINTS = sizeof(waypoints) / sizeof(waypoints[0]);
static int currentWaypointIndex = 0;

// PID tuning parameters
float Kp = 0.02;
float Ki = 0.0005;
float Kd = 0.1;

float headingError = 0;
float previousError = 0;
float integral = 0;
unsigned long lastPIDTime = 0;

// Distance between two GPS points (meters)
float distanceBetween(float lat1, float lon1, float lat2, float lon2) {
  const float R = 6371000;
  float dLat = radians(lat2 - lat1);
  float dLon = radians(lon2 - lon1);
  float a = sin(dLat / 2) * sin(dLat / 2) +
            cos(radians(lat1)) * cos(radians(lat2)) *
            sin(dLon / 2) * sin(dLon / 2);
  return R * 2 * atan2(sqrt(a), sqrt(1 - a));
}

// Bearing from point A to point B
float bearingTo(float lat1, float lon1, float lat2, float lon2) {
  float dLon = radians(lon2 - lon1);
  lat1 = radians(lat1);
  lat2 = radians(lat2);
  float y = sin(dLon) * cos(lat2);
  float x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dLon);
  return fmod((degrees(atan2(y, x)) + 360.0), 360.0);
}

// Cross-track error from path wp1 -> wp2
float calculateCrossTrackError(float lat, float lon,
                               float wp1_lat, float wp1_lon,
                               float wp2_lat, float wp2_lon) {
  const float R = 6371000;
  float d13 = distanceBetween(wp1_lat, wp1_lon, lat, lon);
  float theta13 = radians(bearingTo(wp1_lat, wp1_lon, lat, lon));
  float theta12 = radians(bearingTo(wp1_lat, wp1_lon, wp2_lat, wp2_lon));
  return asin(sin(d13 / R) * sin(theta13 - theta12)) * R;
}

void setupAutopilot() {
  for (int i = 0; i < NUM_WAYPOINTS; i++) {
    waypoints[i].reached = false;
  }
  currentWaypointIndex = 0;
  lastPIDTime = millis();
}

bool allWaypointsReached() {
  return currentWaypointIndex >= NUM_WAYPOINTS;
}

int getCurrentWaypointIndex() {
  return currentWaypointIndex;
}

void runAutopilot() {
  if (allWaypointsReached()) {
    updateMotorPower(0.0);
    centerRudder();
    return;
  }

  GPSData gps = getGPSData();
  IMUData imu = getIMUData();

  if (!gps.valid || !imu.valid) {
    Serial.println("Waiting for valid GPS or IMU...");
    updateMotorPower(0.0);
    return;
  }

  Waypoint& wp2 = waypoints[currentWaypointIndex];
  Waypoint wp1 = (currentWaypointIndex == 0) ? waypoints[0] : waypoints[currentWaypointIndex - 1];

  float distanceToTarget = distanceBetween(gps.latitude, gps.longitude, wp2.latitude, wp2.longitude);

  if (distanceToTarget < WAYPOINT_TOLERANCE_METERS) {
    Serial.println("Waypoint reached.");
    wp2.reached = true;
    currentWaypointIndex++;
    return;
  }

  float crossTrack = calculateCrossTrackError(
      gps.latitude, gps.longitude,
      wp1.latitude, wp1.longitude,
      wp2.latitude, wp2.longitude);

  float pathBearing = bearingTo(wp1.latitude, wp1.longitude, wp2.latitude, wp2.longitude);
  float totalCorrection = pathBearing - imu.yaw;

  if (totalCorrection > 180) totalCorrection -= 360;
  if (totalCorrection < -180) totalCorrection += 360;

  totalCorrection += crossTrack / 10.0; // Adjust gain as needed

  // === PID CONTROL ===
  unsigned long now = millis();
  float dt = (now - lastPIDTime) / 1000.0;
  lastPIDTime = now;

  headingError = totalCorrection;
  integral += headingError * dt;
  float derivative = (headingError - previousError) / dt;
  previousError = headingError;

  float rudderCmd = Kp * headingError + Ki * integral + Kd * derivative;
  rudderCmd = constrain(rudderCmd / 45.0, -1.0, 1.0);

  setRudderPosition(rudderCmd);
  updateMotorPower(MOTOR_CRUISE_POWER);  // Replaces setMotorPower()

  // Debug
  Serial.println("=== AUTOPILOT PID ===");
  Serial.print("Target bearing: "); Serial.println(pathBearing);
  Serial.print("Heading: "); Serial.println(imu.yaw);
  Serial.print("Heading error: "); Serial.println(headingError);
  Serial.print("Cross-track error: "); Serial.println(crossTrack);
  Serial.print("Rudder command: "); Serial.println(rudderCmd);
  Serial.print("Distance to waypoint: "); Serial.println(distanceToTarget);
}
