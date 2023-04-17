#pragma once

#include "Arduino.h"
#include "pins.h"

void fanControl(int state[]) {
  static int fan1_status = state[1];
  static int fan2_status = state[2];
  static int fan3_status = state[3];

  if (fan1_status) {
    digitalWrite(extrdFan_relay, LOW);
  } else {
    digitalWrite(extrdFan_relay, HIGH);
  }
  if (fan2_status) {
    digitalWrite(coolFan_relay, LOW);
  } else {
    digitalWrite(coolFan_relay, HIGH);
  }
  if (fan3_status) {
    digitalWrite(eboxFan_relay, LOW);
  } else {
    digitalWrite(eboxFan_relay, HIGH);
  }
}