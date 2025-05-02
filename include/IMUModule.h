#ifndef IMU_MODULE_H
#define IMU_MODULE_H

#include <Arduino.h>

// Struct to hold IMU data
struct IMUData {
  float roll;     // degrees
  float pitch;    // degrees
  float yaw;      // compass heading (degrees)
  bool valid;
};

// Initialize IMU (call in setup)
void setupIMU();

// Update internal IMU readings (call regularly in loop)
void updateIMU();

// Get the latest IMU orientation
IMUData getIMUData();

#endif
