#ifndef GPS_MODULE_H
#define GPS_MODULE_H

#include <Arduino.h>

// Struct to hold current GPS data
struct GPSData {
  float latitude;
  float longitude;
  float speed_kmph;
  float course_deg;
  int satellites;
  bool valid;
};

// Call once in setup() to initialize GPS
void setupGPS();

// Call regularly in loop() to update GPS data from serial
void updateGPS();

// Get the latest parsed GPS data
GPSData getGPSData();

#endif
