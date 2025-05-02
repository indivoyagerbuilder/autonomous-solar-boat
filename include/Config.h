#ifndef CONFIG_H
#define CONFIG_H

// === Pin Assignments ===

// Motor PWM
#define MOTOR_PWM_PIN        25  // GPIO pin connected to ESC signal wire

// Rudder Servo
#define RUDDER_SERVO_PIN     26  // GPIO pin connected to rudder servo

// GPS UART
#define GPS_RX_PIN           16  // ESP32 receives from GPS
#define GPS_TX_PIN           17  // ESP32 transmits to GPS

// Rockblock UART
#define ROCKBLOCK_RX_PIN     4   // ESP32 receives from Rockblock
#define ROCKBLOCK_TX_PIN     5   // ESP32 transmits to Rockblock
#define ROCKBLOCK_SLEEP_PIN  5   // Optional: control Rockblock sleep pin

// I2C Bus (shared between IMU and INA260s)
#define I2C_SDA_PIN          21
#define I2C_SCL_PIN          22

// RC Manual Override (PWM input)
#define RC_OVERRIDE_PIN      33  // Connected to RC receiver channel

// === Motor PWM Settings ===
#define MOTOR_PWM_MIN        1000  // µs signal for stop/idle
#define MOTOR_PWM_MAX        2000  // µs signal for full thrust

// === Rudder PWM Settings ===
#define RUDDER_PWM_MIN       1000  // µs for full left (not used directly)
#define RUDDER_PWM_CENTER    1500  // µs center
#define RUDDER_PWM_MAX       2000  // µs for full right (not used directly)

// === Battery Settings ===
#define BATTERY_VOLTAGE_FULL   12.6  // Fully charged 12V LiFePO4
#define BATTERY_VOLTAGE_EMPTY  10.5  // Considered empty/discharged

// === Timing Settings ===
#define GPS_UPDATE_INTERVAL_MS     1000    // How often to update GPS
#define TELEMETRY_INTERVAL_MS      60000   // How often to send Rockblock data
#define CONTROL_LOOP_INTERVAL_MS   200     // Autopilot loop rate

#define RC_OVERRIDE_PIN 33  // Adjust based on your wiring


#endif
