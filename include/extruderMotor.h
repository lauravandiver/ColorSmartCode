/* extruderMotor.h
 * Nikolas Prochaska
 * For ColorSmart SFR
 * Definitions and constants for the operation of
 * the extruder motor
 */

#pragma once

#include "pins.h"
#include <Arduino.h>

#define EXTRUDE_SPEED_PWM 20

void extrMInit(void) {
  // Initiallize pin modes for the output to the motor driver
  pinMode(EXTR_DIR, OUTPUT);
  pinMode(EXTR_PWM, OUTPUT);

  digitalWrite(EXTR_DIR, HIGH);
  // Set PWM on pins 2, 3, 5, to ~31000 Hz
  TCCR3B = TCCR3B & (B11111000 | B00000001);
}

void extrudeRun(void) { analogWrite(EXTR_PWM, EXTRUDE_SPEED_PWM); }

void extrudeStop(void) { analogWrite(EXTR_PWM, 0); }