/* hopperStepper.h
 * Nikolas Prochaska
 * For ColorSmart SFR
 * Definitions and constants for the operation of 
 * the hopper dispenser steppers
 */

#ifndef hopperStepper
#define hopperStepper

#ifndef accelStepperDef
#define accelStepperDef
#include <AccelStepper.h>
#endif   // accelStepperDef

#ifndef pins
#include "pins.h"
#endif   // pins

// Distance of forward rotation
#define FWD_DIST 400  // Steps, NOTE: 48 steps per rev.
// Distance of backwards rotation
#define BWD_DIST -100

#define V_MAX 5000   // Max velocity, Steps/sec
#define ACCEL 25000  // Motor acceleration, steps/sec^2

// Set up hoppers in Accel Stepper
AccelStepper hopper1(AccelStepper::DRIVER, h1_STEP, h1_DIR);
AccelStepper hopper2(AccelStepper::DRIVER, h2_STEP, h2_DIR);
AccelStepper hopper3(AccelStepper::DRIVER, h3_STEP, h3_DIR);
AccelStepper hopper4(AccelStepper::DRIVER, h4_STEP, h4_DIR);
AccelStepper hopper5(AccelStepper::DRIVER, h5_STEP, h5_DIR);
AccelStepper hopper6(AccelStepper::DRIVER, h6_STEP, h6_DIR);

void initHoppers() {
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

  if (hopper1.distanceToGo() == 0 && ((Select&(0x1) > 0))) {
    if (h1_D) hopper1.move(BWD_DIST);
    else hopper1.move(FWD_DIST);
    h1_D = !h1_D;
  }
  else if (Select&(0x1) == 0){
    hopper1.stop();
    hopper1.move(0);
  }
  
  if (hopper2.distanceToGo() == 0 && (Select&(0x2) > 0)) {
    if (h2_D) hopper2.move(BWD_DIST);
    else hopper2.move(FWD_DIST);
    h2_D = !h2_D;
  }
  else if (Select&(0x2) == 0){
    hopper2.stop();
    hopper2.move(0);
  }

  if (hopper3.distanceToGo() == 0 && (Select&(0x4) > 0)) {
    if (h3_D) hopper3.move(BWD_DIST);
    else hopper3.move(FWD_DIST);
    h3_D = !h3_D;
  }
  else if (Select&(0x4) == 0){
    hopper3.stop();
    hopper3.move(0);
  }

  if (hopper4.distanceToGo() == 0 && (Select&(0x8) > 0)) {
    if (h4_D) hopper4.move(BWD_DIST);
    else hopper4.move(FWD_DIST);
    h4_D = !h4_D;
  }
  else if (Select&(0x8) == 0){
    hopper4.stop();
    hopper4.move(0);
  }

  if (hopper5.distanceToGo() == 0 && (Select&(0x10) > 0)) {
    if (h5_D) hopper5.move(BWD_DIST);
    else hopper5.move(FWD_DIST);
    h5_D = !h5_D;
  }
  else if (Select&(0x10) == 0){
    hopper5.stop();
    hopper5.move(0);
  }

  if (hopper6.distanceToGo() == 0 && (Select&(0x20) > 0)) {
    if (h6_D) hopper6.move(BWD_DIST);
    else hopper6.move(FWD_DIST);
    h6_D = !h6_D;
  }
  else if (Select&(0x20) == 0){
    hopper6.stop();
    hopper6.move(0);
  }

  hopper1.run();
  hopper2.run();
  hopper3.run();
  hopper4.run();
  hopper5.run();
  hopper6.run();
}

#endif  // hopperStepper
