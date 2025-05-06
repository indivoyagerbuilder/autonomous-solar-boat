#include "MotorControl.h"
#include "Config.h"
#include "BatteryMonitor.h"
#include "PWMUtils.h"  // <- brings in microsecondsToDuty()

#define PWM_CHANNEL_MOTOR    0
#define PWM_FREQ             50
#define PWM_RESOLUTION       16  // 16-bit (0–65535)

void setupMotor() {
  ledcSetup(PWM_CHANNEL_MOTOR, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(MOTOR_PWM_PIN, PWM_CHANNEL_MOTOR);
  ledcWrite(PWM_CHANNEL_MOTOR, microsecondsToDuty(MOTOR_PWM_MIN)); // Start at idle
}

// Throttle: 0.0 to 1.0
void updateMotorPower(float requestedPower) {
  float voltage = getBatteryVoltage();

  if (voltage < BATTERY_VOLTAGE_EMPTY) {
    Serial.println("Battery low – motor off");
    ledcWrite(PWM_CHANNEL_MOTOR, microsecondsToDuty(MOTOR_PWM_MIN));
    return;
  }

  float voltagePercent = (voltage - BATTERY_VOLTAGE_EMPTY) / (BATTERY_VOLTAGE_FULL - BATTERY_VOLTAGE_EMPTY);
  voltagePercent = constrain(voltagePercent, 0.0, 1.0);

  float maxPower;
  if (voltagePercent > 0.8) maxPower = 0.9;
  else if (voltagePercent > 0.6) maxPower = 0.7;
  else if (voltagePercent > 0.4) maxPower = 0.5;
  else if (voltagePercent > 0.3) maxPower = 0.3;
  else maxPower = 0.0;

  float effectivePower = constrain(requestedPower, 0.0, maxPower);
  int pwm = MOTOR_PWM_MIN + (MOTOR_PWM_MAX - MOTOR_PWM_MIN) * effectivePower;

  ledcWrite(PWM_CHANNEL_MOTOR, microsecondsToDuty(pwm));
}
