/* shred.h
 * Devin Cole
 * For ColorSmart SFR
 * Definitions and constants for the operation of
 * the shredder system
 */

#pragma once

#include "pins.h"
#include <Arduino.h>

int pwm_value = 0;

void shredInit() {
  // Initiallize pin modes for the output to the motor driver
  pinMode(SHRED_DIR, OUTPUT);
  pinMode(SHRED_PWM, OUTPUT);
  pinMode(SHRED_SAFETY, INPUT_PULLUP);

  // Set PWM on pins 2, 3, 5, to ~31000 Hz
  TCCR3B = TCCR3B & (B11111000 | B00000001);

} // shredInit()

bool runShred() {
  // put your setup code here, to run once:
  static unsigned long runTime = 0;
  static unsigned long currentTime = 0;
  static unsigned long forwardTime = 1000;
  static unsigned long reverseTime = 7000;
  static unsigned long neutralTime = 1000;
  static unsigned long rampTime = 0;

  static int max_speed = 175;

  static int direction = 1;
  static bool toggle = 0;

  if (!digitalRead(SHRED_SAFETY)) {
    currentTime = millis();
    if (direction == 1) {

      // digitalWrite(SHRED_DIR, HIGH);

      if (pwm_value < max_speed) {
        pwm_value = pwm_value + 5;
      }
      analogWrite(SHRED_PWM, pwm_value);

      // Run shredder motor FORWARD at full speed.
      if (currentTime - runTime >= forwardTime) {
        runTime = currentTime;
        direction = -1;
      } // Send stop command to the motor.

    } else if (direction == -1) {

      if ((pwm_value > 0) && ((currentTime - rampTime >= 10))) {
        pwm_value = pwm_value - 5; // Run at full speed
        rampTime = currentTime;
      }

      if (currentTime - runTime >= neutralTime / 2) {

        if ((pwm_value == 0) && (digitalRead(SHRED_DIR) == LOW) && !toggle) {
          digitalWrite(SHRED_DIR, HIGH);
          toggle = 1;
        } else if ((pwm_value == 0) && (digitalRead(SHRED_DIR) == HIGH) &&
                   !toggle) {
          digitalWrite(SHRED_DIR, LOW);
          toggle = 1;
        }
      }
      analogWrite(SHRED_PWM, pwm_value); // Set PWM value

      if (currentTime - runTime >= neutralTime) {
        if (digitalRead(SHRED_DIR) == HIGH) {
          direction = 1;
          digitalWrite(SHRED_PWM, LOW);
          toggle = 0;
        } else if (digitalRead(SHRED_DIR) == LOW) {
          direction = 0;
          digitalWrite(SHRED_PWM, LOW);
          toggle = 0;
        }
        // direction = 1;
        runTime = currentTime;
        // Serial.print('n');
      }

    } else if (direction == 0) {
      // Begin reverse direction

      // digitalWrite(SHRED_DIR, LOW); // Set direction to reverse

      if (pwm_value < max_speed) {
        pwm_value = pwm_value + 5;
      }
      // Run at full speed
      analogWrite(SHRED_PWM, pwm_value); // Set PWM value

      if (currentTime - runTime >= reverseTime) {
        runTime = currentTime;
        direction = -1;
      } // Send stop command to the motor.
      // direction = 1;
    }
  }

  else {
    analogWrite(SHRED_PWM, 0);
  }
  return digitalRead(SHRED_SAFETY);

} // runShred()

void shredStop() { 
  static unsigned long currentTime = 0;
  static unsigned long rampTime = 0;
  currentTime = millis();
  if ((pwm_value > 0) && ((currentTime - rampTime >= 10))) {
        pwm_value = pwm_value - 5; // Run at full speed
        rampTime = currentTime;
      }
  if(pwm_value <= 0){
    digitalWrite(SHRED_PWM, 0); } // shredStop()
  }
  

void reverseShred() {
  shredStop();
  digitalWrite(SHRED_DIR, HIGH);
  analogWrite(SHRED_PWM, 100);

} // reverseShred()
