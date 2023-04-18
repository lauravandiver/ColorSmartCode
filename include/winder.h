/* winder.h
 * Nikolas Prochaska
 * For ColorSmart SFR
 * Definitions and constants for the operation of
 * the winder system
 */

#pragma once

#include "pins.h"
#include <AccelStepper.h>
#include <TMCStepper.h>

#define WIND_R_SENSE 0.11f // Driver Property
#define W_MAX_V 100000     // Motor max speed
#define W_MIN_V 750        // Motor min speed
#define W_DEF_V 1500       // Motor default speed
#define W_ACCEL 200000     // Motor Acceleration

// Define Driver with software SPI
TMC2130Stepper winder(W_CS_PIN, WIND_R_SENSE, W_SW_MOSI, W_SW_MISO,
                      W_SW_SCK); // Software SPI
using namespace TMC2130_n;

AccelStepper as_winder(AccelStepper::DRIVER, WIND_STEP_PIN, WIND_DIR_PIN);

void winderInit(void) {

  pinMode(W_CS_PIN, OUTPUT);
  pinMode(WIND_EN_PIN, OUTPUT);
  pinMode(WIND_STEP_PIN, OUTPUT);
  pinMode(WIND_DIR_PIN, OUTPUT);
  pinMode(W_SW_MISO, INPUT_PULLUP);
  digitalWrite(WIND_EN_PIN, LOW);

  delay(50);

  // TMC driver parameter setup
  digitalWrite(WIND_EN_PIN, LOW);
  winder.begin();
  winder.toff(4);
  winder.blank_time(24);
  winder.rms_current(900); // mA
  // winder.en_pwm_mode(true);      // Enable extremely quiet stepping
  // winder.pwm_autoscale(true);
  winder.microsteps(16);
  winder.TCOOLTHRS(0x0FFFF); // 20bit max
  winder.THIGH(0x00FFF);
  winder.semin(5);
  winder.semax(2);
  winder.sedn(0b01);

  // AccelStepper init
  as_winder.setMaxSpeed(W_MAX_V);
  as_winder.setAcceleration(W_ACCEL);

  as_winder.enableOutputs();

} // winderInit

// Function to run the winder at a set speed
uint16_t winderRunSpeed(uint16_t w_speed) {
  // Check that input speed is acceptable
  if ((w_speed < W_MIN_V) || (w_speed > W_MAX_V)) {
    w_speed = W_DEF_V;
  }

  // Run the motor at the requested speed
  as_winder.setSpeed(w_speed);
  as_winder.runSpeed();

  return w_speed; // Return the speed the motor is set to
} // winderRunSpeed

void winderStop(void) { as_winder.stop(); } // winderStop
