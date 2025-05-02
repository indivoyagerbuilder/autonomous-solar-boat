#include "IMUModule.h"
#include "Config.h"

#include <Wire.h>
#include <LSM6.h>     // Gyroscope + Accelerometer
#include <LIS3MDL.h>  // Magnetometer

// Create sensor objects
LSM6 imu;
LIS3MDL mag;

IMUData currentIMUData;

void setupIMU() {
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  if (!imu.init()) {
    Serial.println("Failed to detect LSM6!");
    currentIMUData.valid = false;
    return;
  }
  imu.enableDefault();

  if (!mag.init()) {
    Serial.println("Failed to detect LIS3MDL!");
    currentIMUData.valid = false;
    return;
  }
  mag.enableDefault();

  currentIMUData.valid = true;
}

void updateIMU() {
  imu.read();
  mag.read();

  // Simple pitch and roll estimation from accelerometer
  float ax = imu.a.x;
  float ay = imu.a.y;
  float az = imu.a.z;

  // Convert to degrees
  currentIMUData.roll = atan2(ay, az) * 180.0 / PI;
  currentIMUData.pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

  // Simple compass heading from magnetometer
  float mx = mag.m.x;
  float my = mag.m.y;

  float heading = atan2(my, mx) * 180.0 / PI;
  if (heading < 0) heading += 360;
  currentIMUData.yaw = heading;
}

IMUData getIMUData() {
  return currentIMUData;
}
