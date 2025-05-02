#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#include <Arduino.h>

// Waypoint struct
struct Waypoint {
  float latitude;
  float longitude;
  bool reached;
};

// Initialize autopilot system
void setupAutopilot();

// Run one navigation/control loop
void runAutopilot();

// Returns true if all waypoints have been completed
bool allWaypointsReached();

// Access current waypoint index (for telemetry/logging)
int getCurrentWaypointIndex();

#endif
