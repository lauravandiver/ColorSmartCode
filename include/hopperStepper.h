/* hopperStepper.h
 * Nikolas Prochaska
 * For ColorSmart SFR
 * Definitions and constants for the operation of
 * the hopper dispenser steppers
 */

#pragma once

#include "pins.h"
#include <AccelStepper.h>

// Distance of forward rotation
#define FWD_DIST -3600 // Steps, NOTE: 3200 steps per rev.
// Distance of backwards rotation
#define BWD_DIST 800

#define V_MAX 6400  // Max velocity, Steps/sec
#define ACCEL 250000 // Motor acceleration, steps/sec^2

// Set up hoppers in Accel Stepper
AccelStepper hopper1(AccelStepper::DRIVER, h1_STEP, h1_DIR);
AccelStepper hopper2(AccelStepper::DRIVER, h2_STEP, h2_DIR);
AccelStepper hopper3(AccelStepper::DRIVER, h3_STEP, h3_DIR);
AccelStepper hopper4(AccelStepper::DRIVER, h4_STEP, h4_DIR);
AccelStepper hopper5(AccelStepper::DRIVER, h5_STEP, h5_DIR);
AccelStepper hopper6(AccelStepper::DRIVER, h6_STEP, h6_DIR);

void hoppersInit() {
  // Assign motor max speeds and accelerations
  hopper1.setMaxSpeed(V_MAX);
  hopper1.setAcceleration(ACCEL);
  hopper2.setMaxSpeed(V_MAX);
  hopper2.setAcceleration(ACCEL);
  hopper3.setMaxSpeed(V_MAX);
  hopper3.setAcceleration(ACCEL);
  hopper4.setMaxSpeed(V_MAX);
  hopper4.setAcceleration(ACCEL);
  hopper5.setMaxSpeed(V_MAX);
  hopper5.setAcceleration(ACCEL);
  hopper6.setMaxSpeed(V_MAX);
  hopper6.setAcceleration(ACCEL);

  hopper1.enableOutputs();
  hopper2.enableOutputs();
  hopper3.enableOutputs();
  hopper4.enableOutputs();
  hopper5.enableOutputs();
  hopper6.enableOutputs();
}

void runHoppers(uint8_t Select) {

  static bool h1_D;
  static bool h2_D;
  static bool h3_D;
  static bool h4_D;
  static bool h5_D;
  static bool h6_D;

  if (hopper1.distanceToGo() == 0 && (((Select & (0b00000001)) > 0))) {
    
    if (h1_D) {
      hopper1.move(BWD_DIST);
    } else {
      hopper1.move(FWD_DIST);
    }
    h1_D = !h1_D;
    
  } else if ((Select & (0b00000001)) == 0) {
    hopper1.move(0);
    //hopper1.stop();
  }

  if (hopper2.distanceToGo() == 0 && ((Select & (0b00000010)) > 0)) {
    if (h2_D) {
      hopper2.move(BWD_DIST);
    } else {
      hopper2.move(FWD_DIST);
    }
    h2_D = !h2_D;
  } else if ((Select & (0b00000010)) == 0) {
    hopper2.move(0);
    //hopper2.stop();
  }

  if (hopper3.distanceToGo() == 0 && ((Select & (0b00000100)) > 0)) {
    if (h3_D) {
      hopper3.move(BWD_DIST);
    } else {
      hopper3.move(FWD_DIST);
    }
    h3_D = !h3_D;
  } else if ((Select & (0b00000100)) == 0) {
    hopper3.move(0);
    //hopper3.stop();
  }

  if (hopper4.distanceToGo() == 0 && ((Select & (0b00001000)) > 0)) {
    if (h4_D) {
      hopper4.move(-BWD_DIST);
    } else {
      hopper4.move(-FWD_DIST);
    }
    h4_D = !h4_D;
  } else if ((Select & (0b00001000)) == 0) {
    hopper4.move(0);
    //hopper4.stop();
  }

  if (hopper5.distanceToGo() == 0 && ((Select & (0b00010000)) > 0)) {
    if (h5_D) {
      hopper5.move(BWD_DIST);
    } else {
      hopper5.move(FWD_DIST);
    }
    h5_D = !h5_D;
  } else if ((Select & (0b00010000)) == 0) {
    hopper5.move(0);
    //hopper5.stop();
  }

  if (hopper6.distanceToGo() == 0 && ((Select & (0b00100000)) > 0)) {
    if (h6_D) {
      hopper6.move(-BWD_DIST);
    } else {
      hopper6.move(-FWD_DIST);
    }
    h6_D = !h6_D;
  } else if ((Select & (0b00100000)) == 0) {
    hopper6.move(0);
    //hopper6.stop();
  }

  if((Select & (0b00000001)) > 0){
    //hopper1.setSpeed(V_MAX);
    hopper1.run();
  }
  if((Select & (0b00000010)) > 0){
    //hopper2.setSpeed(V_MAX);
    hopper2.run();
  }
  if((Select & (0b00000100)) > 0){
    //hopper3.setSpeed(V_MAX);
    hopper3.run();
  }
  if((Select & (0b00001000)) > 0){
    //hopper4.setSpeed(V_MAX);
    hopper4.run();
  }
  if((Select & (0b00010000)) > 0){
    //hopper5.setSpeed(V_MAX);
    hopper5.run();
  }
  if((Select & (0b00100000)) > 0){
    //hopper6.setSpeed(V_MAX);
    hopper6.run();
  }

  // Serial.print(hopper1.distanceToGo());
  // Serial.print("  ");
  // Serial.print(hopper2.distanceToGo());
  // Serial.print("  ");
  // Serial.print(hopper3.distanceToGo());
  // Serial.print("  ");
  // Serial.print(hopper4.distanceToGo());
  // Serial.print("  ");
  // Serial.print(hopper5.distanceToGo());
  // Serial.print("  ");
  // Serial.println(hopper6.distanceToGo());
}
