#include "BatteryMonitor.h"
#include "Config.h"
#include <Wire.h>
#include <Adafruit_INA260.h>

// Create instances for each INA260
Adafruit_INA260 sensor_battery;
Adafruit_INA260 sensor_motor;
Adafruit_INA260 sensor_solar;

// Track if they were found
bool sensorBatteryFound = false;
bool sensorMotorFound = false;
bool sensorSolarFound = false;

void setupBatteryMonitors() {
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  // Sensor 1: Battery at 0x40
  sensorBatteryFound = sensor_battery.begin(0x40);
  if (sensorBatteryFound) Serial.println("Battery sensor (0x40) initialized.");
  else Serial.println("Battery sensor not found!");

  // Sensor 2: Motor at 0x41
  sensorMotorFound = sensor_motor.begin(0x41);
  if (sensorMotorFound) Serial.println("Motor sensor (0x41) initialized.");
  else Serial.println("Motor sensor not found!");

  // Sensor 3: Solar panel at 0x44
  sensorSolarFound = sensor_solar.begin(0x44);
  if (sensorSolarFound) Serial.println("Solar sensor (0x44) initialized.");
  else Serial.println("Solar sensor not found!");
}

PowerData readPowerSensor(SensorID id) {
  PowerData data;
  data.valid = false;

  Adafruit_INA260* sensor;
  bool sensorAvailable = false;

  // Select the correct sensor
  switch (id) {
    case SENSOR_BATTERY:
      sensor = &sensor_battery;
      sensorAvailable = sensorBatteryFound;
      break;
    case SENSOR_MOTOR:
      sensor = &sensor_motor;
      sensorAvailable = sensorMotorFound;
      break;
    case SENSOR_SOLAR:
      sensor = &sensor_solar;
      sensorAvailable = sensorSolarFound;
      break;
  }

  if (!sensorAvailable) return data;

  // Read values
  data.voltage = sensor->readBusVoltage() / 1000.0;
  data.current = sensor->readCurrent() / 1000.0;
  data.power = sensor->readPower() / 1000.0;
  data.valid = true;

  return data;
}

// === New helper for convenience ===
float getBatteryVoltage() {
  PowerData data = readPowerSensor(SENSOR_BATTERY);
  return data.valid ? data.voltage : 0.0;
}
