#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

// Setup motor PWM
void setupMotor();

// Set power from 0.0 to 1.0 (auto-managed based on battery)
void updateMotorPower(float requestedPower);

// Stop motor
void stopMotor();

#endif