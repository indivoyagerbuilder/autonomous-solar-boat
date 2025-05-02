#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

// Initialize motor control (call in setup)
void setupMotor();

// Set motor thrust (0.0 to 1.0 = forward power)
void setMotorPower(float power);

// Stop motor completely
void stopMotor();

#endif
