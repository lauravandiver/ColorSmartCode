/* aligner.h
 * Nikolas Prochaska
 * For ColorSmart SFR
 * Definitions and constants for the operation of 
 * the aligner system
 */

#pragma once

#include <AccelStepper.h>
#include <TMCStepper.h>
#include "pins.h"

#define STALL_VALUE      21     // [-64..63]; Tune to application

#define ALIGN_R_SENSE    0.11f    // Driver Property
#define AL_MAX_V         100000   // Motor max speed
#define AL_ACCEL         200000   // Motor Acceleration
#define AL_HOME_SPEED    -5000    // Motor speed during Home process
#define AL_OP_SPEED      4059     // Motor speed during normal operation 2706
#define AL_MAX_POS       162560     // Operation travel upper bound
#define AL_MIN_POS       200      // Operation travel lower bound
#define AL_OP_STEP       200      //

// Define Driver with software SPI
TMC2130Stepper aligner(AL_CS_PIN, ALIGN_R_SENSE, AL_SW_MOSI, AL_SW_MISO, AL_SW_SCK); // Software SPI
using namespace TMC2130_n;

AccelStepper as_aligner(AccelStepper::DRIVER, ALIGN_STEP_PIN, ALIGN_DIR_PIN);

void alignerInit(void){

  pinMode(AL_CS_PIN, OUTPUT);
  pinMode(ALIGN_EN_PIN, OUTPUT);
  pinMode(ALIGN_STEP_PIN, OUTPUT);
  pinMode(ALIGN_DIR_PIN, OUTPUT);
  pinMode(AL_SW_MISO, INPUT_PULLUP);
  pinMode(AL_DIAG1, INPUT_PULLUP);
  digitalWrite(ALIGN_EN_PIN, LOW);

  SPI.begin();
  delay(50);

  // TMC driver parameter setup
  digitalWrite(ALIGN_EN_PIN,LOW);
  aligner.begin();
  aligner.toff(4);
  aligner.blank_time(24);
  aligner.rms_current(700); // mA
  //aligner.en_pwm_mode(true);      // Enable extremely quiet stepping
  //aligner.pwm_autoscale(true);
  aligner.microsteps(16);
  aligner.TCOOLTHRS(0x0FFFF); // 20bit max
  aligner.THIGH(0x00FFF);
  aligner.semin(5);
  aligner.semax(2);
  aligner.sedn(0b01);
  aligner.diag1_stall(1);   // Enable active low ouptut of Diag1 when stalled
  aligner.sgt(STALL_VALUE);

  // AccelStepper init
  as_aligner.setMaxSpeed(AL_MAX_V);
  as_aligner.setAcceleration(AL_ACCEL);

  as_aligner.enableOutputs();

}   // alignerInit

bool alignerHome(void){
  //uint32_t last_time=0;
  //uint32_t ms = millis();
  as_aligner.setSpeed(AL_HOME_SPEED);
  do{
    as_aligner.runSpeed();
    //ms = millis();
    //if((ms-last_time) > 100) { //run every 0.1s
      //last_time = ms;
      //DRV_STATUS_t drv_status{0};
      //drv_status.sr = aligner.DRV_STATUS();
      //Serial.print(as_aligner.speed(), DEC);
      //Serial.print(" ");
      //Serial.print(digitalRead(AL_DIAG1));
      //Serial.print(" ");
      //Serial.print(drv_status.sg_result, DEC);
      //Serial.print(" ");
      //Serial.println(aligner.cs2rms(drv_status.cs_actual), DEC);
    //}
  }while(digitalRead(AL_DIAG1));

  as_aligner.stop();
  as_aligner.setCurrentPosition(0);
  //Serial.println("Homed!");

  digitalWrite(ALIGN_EN_PIN, HIGH);
  as_aligner.setSpeed(AL_OP_SPEED);

  return true;
}

void alignerRun(void){
  static bool runFwd = true;
  digitalWrite(ALIGN_EN_PIN, LOW);

  if(runFwd && as_aligner.currentPosition() > AL_MAX_POS){
    as_aligner.setSpeed(-AL_OP_SPEED);
    runFwd = false;
    //Serial.print(as_aligner.currentPosition());
    //Serial.print("  ");
    //Serial.println("Reverse");
  }

  if(!runFwd && as_aligner.currentPosition() < AL_MIN_POS){
    as_aligner.setSpeed(AL_OP_SPEED);
    runFwd = true;
    //Serial.print(as_aligner.currentPosition());
    //Serial.print("  ");
    //Serial.println("Forward");
  }
  as_aligner.runSpeed();
}