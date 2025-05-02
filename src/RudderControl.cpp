#include "RudderControl.h"
#include "Config.h"

// Define PWM settings
#define RUDDER_PWM_CHANNEL   1       // Use a different channel than motor
#define RUDDER_PWM_FREQ      50      // 50 Hz = 20 ms period (standard for servos)
#define RUDDER_PWM_RES       16      // 16-bit resolution (0–65535)

// Helper: convert microseconds to 16-bit duty cycle
uint32_t microsecondsToDuty(int microseconds) {
  return (microseconds * 65535UL) / 20000UL;  // 20,000 µs period at 50 Hz
}

void setupRudder() {
  ledcSetup(RUDDER_PWM_CHANNEL, RUDDER_PWM_FREQ, RUDDER_PWM_RES);
  ledcAttachPin(RUDDER_SERVO_PIN, RUDDER_PWM_CHANNEL);
  centerRudder();
}

void setRudderPosition(float position) {
  // Clamp input to range [-1.0, 1.0]
  position = constrain(position, -1.0, 1.0);

  // Convert position to microsecond pulse
  int pulse = 1500 + position * 500;  // +/- 500 µs from center
  uint32_t duty = microsecondsToDuty(pulse);
  ledcWrite(RUDDER_PWM_CHANNEL, duty);
}

void centerRudder() {
  uint32_t duty = microsecondsToDuty(1500);
  ledcWrite(RUDDER_PWM_CHANNEL, duty);
}

