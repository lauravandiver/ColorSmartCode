#pragma once
#include "pins.h"

void fanControl(int state[]) {
  static int fan1_status = state[1];
  static int fan2_status = state[2];
  static int fan3_status = state[3];

  if (fan1_status) {
    digitalWrite(fanRelay_1, LOW);
  } else {
    digitalWrite(fanRelay_1, HIGH);
  }
  if (fan2_status) {
    digitalWrite(fanRelay_2, LOW);
  } else {
    digitalWrite(FanRelay_2, HIGH);
  }
  if (fan3_status) {
    digitalWrite(fanRelay_3, LOW);
  } else {
    digitalWrite(fanRelay_3, HIGH);
  }
}