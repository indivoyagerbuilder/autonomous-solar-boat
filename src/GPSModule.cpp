#include "GPSModule.h"
#include "Config.h"          // Pin definitions and constants
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Create a GPS object from TinyGPS++
TinyGPSPlus gps;

// Use a hardware serial port (UART2 on ESP32)
HardwareSerial GPSSerial(2); // UART2

// Store the most recent GPS data
GPSData currentData;

// Set up the GPS module
void setupGPS() {
  // Begin communication with the GPS module
  GPSSerial.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  Serial.println("GPS module initialized");
}

// Continuously read data from the GPS and update currentData
void updateGPS() {
  while (GPSSerial.available() > 0) {
    gps.encode(GPSSerial.read());
  }

  // Check if we have a valid location fix
  currentData.valid = gps.location.isValid();

  // If we do, update the stored data
  if (currentData.valid) {
    currentData.latitude = gps.location.lat();
    currentData.longitude = gps.location.lng();
    currentData.speed_kmph = gps.speed.kmph();       // Speed in km/h
    currentData.course_deg = gps.course.deg();       // Heading in degrees
    currentData.satellites = gps.satellites.value(); // Number of satellites
  }
}

// Get the last known GPS data
GPSData getGPSData() {
  return currentData;
}
