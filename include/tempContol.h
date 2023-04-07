#pragma once
// Set up thermocouples

#include "MAX6675.h"
#include "pins.h"

// set up thermocouples
MAX6675 thermocouple1(thermoCLK, thermoCS, thermoDO1);
MAX6675 thermocouple2(thermoCLK, thermoCS, thermoDO2);
MAX6675 thermocouple3(thermoCLK, thermoCS, thermoDO3);

int gettemp1() { return thermocouple1.readCelsius(); }

int gettemp2() { return thermocouple2.readCelsius(); }
int gettemp3() { return thermocouple3.readCelsius(); }

bool startExtruder(int destemp) {
  static int destemp1 = destemp;
  static int destemp2 = destemp1 - 40;
  static int destemp3 = destemp2 - 60;

  static bool zone1_done = false;
  static bool zone2_done = false;
  static bool zone3_done = false;

  static int overshoot1 = 20;
  static int overshoot2 = 40;
  static int overshoot3 = 60;

  if (gettemp1() < (destemp1 - overshoot1) && !zone1_done) {
    digitalWrite(relay_1, LOW);
  } else if (gettemp1() >= (destemp1 - overshoot1)) {
    zone1_done = true;
  }

  if (gettemp2() < (destemp2 - overshoot2) && (zone1_done && !zone2_done)) {
    digitalWrite(relay_2, LOW);
    // checktemps();
  } else if (gettemp2() >= (destemp2 - overshoot2)) {
    zone2_done = true;
  }

  if (gettemp3() < (destemp3 - overshoot3) &&
      (zone1_done && zone2_done && !zone3_done)) {
    digitalWrite(relay_3, LOW);
  } else if (gettemp3() >= (destemp3 - overshoot3)) {
    zone3_done = true;
  }

  // Determine if start is done. If so reset so it can be called again
  if (zone1_done && zone2_done && zone3_done) {
    zone1_done = false;
    zone2_done = false;
    zone3_done = false;

    return true;
  } else
    return false;

} // startExtruder()

void adjusttemps(int destemp) {
  static int destemp1 = destemp;
  static int destemp2 = destemp1 - 40;
  static int destemp3 = destemp2 - 60;

  static int undershoot = 1;

  // Adjust temp1
  if (gettemp1() <= (destemp1 + undershoot)) {
    digitalWrite(relay_1, LOW);
  } else {
    digitalWrite(relay_1, HIGH);
  }
  // Adjust temp2
  if (gettemp2() <= (destemp2 + undershoot)) {
    digitalWrite(relay_2, LOW);
  } else {
    digitalWrite(relay_2, HIGH);
  }
  // Adjust temp3
  //  if (gettemp3() <= (destemp3 + undershoot)){
  //    digitalWrite(relay_3, LOW);
  //  }
  //  else{
  //    digitalWrite(relay_3, HIGH);
  //  }
}

void fanControl(int state) {
  if (state) {
    digitalWrite(relay_2, LOW);
  } else {
    digitalWrite(relay_2, HIGH);
  }
}

void extrudOff() {
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);
}
