#include "MotorControl.h"
#include "Config.h"

// PWM setup
#define PWM_CHANNEL     0          // LEDC channel (ESP32 supports 16)
#define PWM_FREQ        50         // 50 Hz for ESCs
#define PWM_RESOLUTION  16         // 16-bit resolution (0–65535 range)

// Convert microseconds (ESC pulse width) to duty cycle
uint32_t microsecondsToDuty(int microseconds) {
  // For 50Hz, period = 20,000 µs (20ms)
  // Full duty = 65535 -> 20000 µs
  return (microseconds * 65535UL) / 20000UL;
}

void setupMotor() {
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);         // Set up PWM
  ledcAttachPin(MOTOR_PWM_PIN, PWM_CHANNEL);                 // Attach pin
  stopMotor();
}

// power: 0.0 = stopped, 1.0 = full forward
void setMotorPower(float power) {
  power = constrain(power, 0.0, 1.0);                        // Clamp power
  int pulseWidth = MOTOR_PWM_MIN + power * (MOTOR_PWM_MAX - MOTOR_PWM_MIN);
  uint32_t duty = microsecondsToDuty(pulseWidth);
  ledcWrite(PWM_CHANNEL, duty);
}

// Immediately stop motor
void stopMotor() {
  uint32_t duty = microsecondsToDuty(MOTOR_PWM_MIN);        // Minimum PWM signal
  ledcWrite(PWM_CHANNEL, duty);
}
