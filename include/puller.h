/* puller.h
 * Nikolas Prochaska
 * For ColorSmart SFR
 * Definitions and constants for the operation of 
 * the puller system
 */

#pragma once

#include <AccelStepper.h>
#include <TMCStepper.h>
#include "pins.h"

#define PULL_R_SENSE     0.11f    // Driver Property
#define PU_MAX_V         100000   // Motor max speed
#define PU_MIN_V         750      // Motor min speed
#define PU_DEF_V         1500     // Motor default speed
#define PU_ACCEL         200000   // Motor Acceleration

// Define Driver with software SPI
TMC2130Stepper puller(PU_CS_PIN, PULL_R_SENSE, PU_SW_MOSI, PU_SW_MISO, PU_SW_SCK); // Software SPI
using namespace TMC2130_n;

AccelStepper as_puller(AccelStepper::DRIVER, PULL_STEP_PIN, PULL_DIR_PIN);

void pullerInit(void){

  pinMode(PU_CS_PIN, OUTPUT);
  pinMode(PULL_EN_PIN, OUTPUT);
  pinMode(PULL_STEP_PIN, OUTPUT);
  pinMode(PULL_DIR_PIN, OUTPUT);
  pinMode(PU_SW_MISO, INPUT_PULLUP);
  digitalWrite(PULL_EN_PIN, LOW);

  delay(50);

  // TMC driver parameter setup
  digitalWrite(PULL_EN_PIN,LOW);
  puller.begin();
  puller.toff(4);
  puller.blank_time(24);
  puller.rms_current(700); // mA
  //puller.en_pwm_mode(true);      // Enable extremely quiet stepping
  //puller.pwm_autoscale(true);
  puller.microsteps(16);
  puller.TCOOLTHRS(0x0FFFF); // 20bit max
  puller.THIGH(0x00FFF);
  puller.semin(5);
  puller.semax(2);
  puller.sedn(0b01);


  // AccelStepper init
  as_puller.setMaxSpeed(PU_MAX_V);
  as_puller.setAcceleration(PU_ACCEL);

  as_puller.enableOutputs();

}   // pullerInit

// Function to run the puller at a set speed
uint16_t pullerRunSpeed(uint16_t p_speed){
  //Check that input speed is acceptable
  if((p_speed < PU_MIN_V) || (p_speed > PU_MAX_V)){ p_speed = PU_DEF_V; }

  // Run the motor at the requested speed
  as_puller.setSpeed(p_speed);
  as_puller.runSpeed();

  return p_speed; // Return the speed the motor is set to
} // pullerRunSpeed

void pullerStop(void){
  as_puller.stop();
} // pullerStop
