// Set up thermocouples

#include "MAX6675.h"
#include "pins.h"

#pragma once

// set up thermocouples
MAX6675 thermocouple1(thermoCLK1, thermoCS1, thermoDO1);
MAX6675 thermocouple2(thermoCLK2, thermoCS2, thermoDO2);
MAX6675 thermocouple3(thermoCLK3, thermoCS3, thermoDO3);

int gettemp1() { return thermocouple1.readCelsius(); }
int gettemp2() { return thermocouple2.readCelsius(); }
int gettemp3() { return thermocouple3.readCelsius(); }

void tempInit(void) {
  // pinMode(thermoCLK1, OUTPUT);
  // pinMode(thermoCS1, OUTPUT);
  // pinMode(thermoDO1, INPUT);
  // pinMode(thermoCLK2, OUTPUT);
  // pinMode(thermoCS2, OUTPUT);
  // pinMode(thermoDO2, INPUT);
  // pinMode(thermoCLK3, OUTPUT);
  // pinMode(thermoCS3, OUTPUT);
  // pinMode(thermoDO3, INPUT);

  pinMode(HB1_relay, OUTPUT);
  pinMode(HB2_relay, OUTPUT);
  pinMode(HB3_relay, OUTPUT);
}

bool startExtruder(int destemp) {
  static int destemp1 = destemp;
  static int destemp2 = destemp1 - 40;
  // static int destemp3 = destemp2 - 60;

  static bool zone1_done = false;
  static bool zone2_done = false;
  static bool zone3_done = true; // not monitoring zone 3 bc hb is off

  static int overshoot1 = 20;
  static int overshoot2 = 40;
  // static int overshoot3 = 60;

  static unsigned long lastTime = 0;
  static unsigned long currentTime = 0;

  int t1, t2, t3;

  currentTime = millis();
  if ((currentTime - lastTime) >= 250) {
    t1 = gettemp1();
    t2 = gettemp2();
    t3 = gettemp3();
    lastTime = currentTime;
  }

  if (t1 < (destemp1 - overshoot1) && !zone1_done) {
    digitalWrite(HB1_relay, HIGH);
  } else if (t1 >= (destemp1 - overshoot1)) {
    zone1_done = true;
    digitalWrite(HB1_relay, LOW);
  }

  if (t2 < (destemp2 - overshoot2) && (zone1_done && !zone2_done)) {
    digitalWrite(HB2_relay, HIGH);
  } else if (t2 >= (destemp2 - overshoot2)) {
    zone2_done = true;
    digitalWrite(HB2_relay, LOW);
  }

  // if (t3 < (destemp3 - overshoot3) &&
  //     (zone1_done && zone2_done && !zone3_done)) {
  //   digitalWrite(HB3_relay, HIGH);
  // } else if (t3 >= (destemp3 - overshoot3)) {
  //   zone3_done = true;
  //   digitalWrite(HB3_relay, LOW);
  // }

  // Determine if start is done. If so reset so it can be called again
  if (zone1_done && zone2_done && zone3_done) {
    zone1_done = false;
    zone2_done = false;
    // zone3_done = false;

    Serial.println("Startup Done!");
    return true;
  } else

    return false;

} // startExtruder()

void adjusttemps(int destemp) {
  static int destemp1 = destemp;
  static int destemp2 = destemp1 - 40;
  // static int destemp3 = destemp2 - 60;

  static int undershoot = 1;

  static unsigned long lastTime = 0;
  static unsigned long currentTime = 0;

  int t1, t2, t3;

  currentTime = millis();
  if ((currentTime - lastTime) >= 250) {
    t1 = gettemp1();
    t2 = gettemp2();
    t3 = gettemp3();
    lastTime = currentTime;
  }

  // Adjust temp1
  if (t1 <= (destemp1 + undershoot)) {
    digitalWrite(HB1_relay, HIGH);
  } else {
    digitalWrite(HB1_relay, LOW);
  }
  // Adjust temp2
  if (t2 <= (destemp2 + undershoot)) {
    digitalWrite(HB2_relay, HIGH);
  } else {
    digitalWrite(HB2_relay, LOW);
  }
  // Adjust temp3
  //  if (t3 <= (destemp3 + undershoot)){
  //    digitalWrite(HB3_relay, HIGH);
  //  }
  //  else{
  //    digitalWrite(HB3_relay, LOW);
  //  }
}

void extrudOff() {
  digitalWrite(HB1_relay, LOW);
  digitalWrite(HB2_relay, LOW);
  digitalWrite(HB3_relay, LOW);
}
