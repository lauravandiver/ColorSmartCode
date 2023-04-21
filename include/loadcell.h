/* loadcell.h
 * Nikolas Prochaska
 * For ColorSmart SFR
 * Definitions and constants for the operation of
 * the loadcells used to weigh the material hoppers
 */

#pragma once

#include "pins.h"
#include <HX711.h>

HX711 lcH1;
HX711 lcH2;
HX711 lcH3;
HX711 lcH4;
HX711 lcH5;
HX711 lcH6;

#define CAL_FACT -705500
#define OP_DELAY 100 // Delay between reading different loadcells
long zero_factor = -564541;

// Initalize loadcells and set their calibration factors and offsets
void loadcellInit(void) {
  // Primary initialization and pin relations
  lcH1.begin(LCH1_DOUT_PIN, LCH1_SCK_PIN);
  delay(OP_DELAY);
  lcH2.begin(LCH2_DOUT_PIN, LCH2_SCK_PIN);
  delay(OP_DELAY);
  lcH3.begin(LCH3_DOUT_PIN, LCH3_SCK_PIN);
  delay(OP_DELAY);
  lcH4.begin(LCH4_DOUT_PIN, LCH4_SCK_PIN);
  delay(OP_DELAY);
  lcH5.begin(LCH5_DOUT_PIN, LCH5_SCK_PIN);
  delay(OP_DELAY);
  lcH6.begin(LCH6_DOUT_PIN, LCH6_SCK_PIN);
  delay(OP_DELAY);

  // Set calibration factor
  lcH1.set_scale(CAL_FACT);
  delay(OP_DELAY);
  lcH2.set_scale(CAL_FACT);
  delay(OP_DELAY);
  lcH3.set_scale(CAL_FACT);
  delay(OP_DELAY);
  lcH4.set_scale(CAL_FACT);
  delay(OP_DELAY);
  lcH5.set_scale(CAL_FACT);
  delay(OP_DELAY);
  lcH6.set_scale(CAL_FACT);
  delay(OP_DELAY);

  // "tare" the loadcells for hopper weight
  lcH1.set_offset(zero_factor);
  delay(OP_DELAY);
  lcH2.set_offset(zero_factor);
  delay(OP_DELAY);
  lcH3.set_offset(zero_factor);
  delay(OP_DELAY);
  lcH4.set_offset(zero_factor);
  delay(OP_DELAY);
  lcH5.set_offset(zero_factor);
  delay(OP_DELAY);
  lcH6.set_offset(zero_factor);
  delay(OP_DELAY);

} // loadcellInit

// Tare designated loadcell by taking an average reading
// and update offset based on this reading
void loadcellTare(int lc) {

  long tare1, tare2, tare3, tare4, tare5, tare6;

  switch (lc) {
  case 1:
    tare1 = lcH1.read_average(1);
    delay(OP_DELAY);
    lcH1.set_offset(tare1);
    break;
  case 2:
    tare2 = lcH2.read_average(1);
    delay(OP_DELAY);
    lcH2.set_offset(tare2);
    break;
  case 3:
    tare3 = lcH3.read_average(1);
    delay(OP_DELAY);
    lcH3.set_offset(tare3);
    break;
  case 4:
    tare4 = lcH4.read_average(1);
    delay(OP_DELAY);
    lcH4.set_offset(tare4);
    break;
  case 5:
    tare5 = lcH5.read_average(1);
    delay(OP_DELAY);
    lcH5.set_offset(tare5);
    break;
  case 6:
    tare6 = lcH6.read_average(1);
    delay(OP_DELAY);
    lcH6.set_offset(tare6);
    break;
  }

  // zero_factor = tare4;

} // loadcellInit

// Read a designated hopper and return the value in grams
int readLoadCell(int hopper) {
  float reading = 0;
  int grams;

  switch (hopper) {
  case 1:
    reading = 1000 * lcH1.get_units();
    break;
  case 2:
    reading = 1000 * lcH2.get_units();
    break;
  case 3:
    reading = 1000 * lcH3.get_units();
    break;
  case 4:
    reading = 1000 * lcH4.get_units();
    break;
  case 5:
    reading = 1000 * lcH5.get_units();
    break;
  case 6:
    reading = 1000 * lcH6.get_units();
    break;
  default:
    break;
  } // switch hoppper

  // Serial.println(reading);
  grams = (int)reading;

  return grams;

} // read_loadcell
