#include "RudderControl.h"
#include "Config.h"
#include "PWMUtils.h"  // <-- brings in microsecondsToDuty()

#define PWM_CHANNEL_RUDDER     1
#define PWM_FREQ               50
#define PWM_RESOLUTION         16  // 16-bit

void setupRudder() {
  ledcSetup(PWM_CHANNEL_RUDDER, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(RUDDER_PWM_PIN, PWM_CHANNEL_RUDDER);
  centerRudder();
}

void setRudderPosition(float position) {
  position = constrain(position, -1.0, 1.0);
  int pwm = RUDDER_PWM_CENTER + position * (RUDDER_PWM_MAX - RUDDER_PWM_CENTER);
  ledcWrite(PWM_CHANNEL_RUDDER, microsecondsToDuty(pwm));
}

void centerRudder() {
  ledcWrite(PWM_CHANNEL_RUDDER, microsecondsToDuty(RUDDER_PWM_CENTER));
}
