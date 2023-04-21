/* digitalIndicator.h
 * Nikolas Prochaska
 * For ColorSmart SFR
 * Definitions and constants for the operation of
 * the Mitutoyo digitimatic indicator used for diameter
 * measurement of the produced filament.
 */

#pragma once

#include "pins.h"
#include <string.h>

// Configure indicator pins
void indicatorInit(void) {
  pinMode(DIA_CLK_PIN, INPUT_PULLUP);
  pinMode(DIA_REQ_PIN, OUTPUT);
  pinMode(DIA_DATA_PIN, INPUT_PULLUP);

  digitalWrite(DIA_REQ_PIN, HIGH); // Non-request state

} // indicatorInit()

// Take reading from digital indiactor and report
// value in millimeters
float indicatorReadMM() {
  // Iterataion variables
  int i = 0; // Byte iteration
  int j = 0; // Bits iteration

  // Parts of input signal
  int sign = 0;     // Sign bit from reading
  int decimal;      // Decimal place identifier from reading
  int units;        // Units identifier from reading
  int in_byte = 0;  // Variable to have bits written to
  byte in_data[14]; // Compiled bits of input
  String value_str;

  // Processing variables
  float decimal_multiplier; // Multiplier to shift reading to correct decimal
  float value;              // Finalized reading value

  digitalWrite(DIA_REQ_PIN, LOW); // Start data request

  //  Read in the 13 incoming bytes
  for (i = 0; i < 13; i++) {
    in_byte = 0;

    // Read in the 4 bits per byte
    for (j = 0; j < 4; j++) {
      // Wait to read at the falling edge of clk
      while (digitalRead(DIA_CLK_PIN) == LOW) {
      } // Wait for clk to go high
      while (digitalRead(DIA_CLK_PIN) == HIGH) {
      } // Wait for clk to go low

      // Read the current bit and write to in_byte in place j (restores
      // rightmost LSB)
      bitWrite(in_byte, j, digitalRead(DIA_DATA_PIN));

    } // Read byte loop

    in_data[i] = in_byte; // Store recieved bit

  } // Data stream loop
  digitalWrite(DIA_REQ_PIN, HIGH);

  // Serial.print("0x");
  // for (int i = 0; i < 14; ++i) {

  //   Serial.print(in_data[i], 16);
  // }
  // Serial.println();

  sign = in_data[4];     // Separate the sign byte
  units = in_data[12];   // Separate the units byte
  decimal = in_data[11]; // Separate decimal place byte

  // Convert D6 thru D11 digits to a number
  value_str = String(in_data[5]) + String(in_data[6]) + String(in_data[7]) +
              String(in_data[8]) + String(in_data[9]) + String(in_data[10]);
  value = (float)value_str.toInt();

  // Decide which power of ten the measurement is in
  if (decimal == 0)
    decimal_multiplier = 1.0;
  else if (decimal == 1)
    decimal_multiplier = 10.0;
  else if (decimal == 2)
    decimal_multiplier = 100.0;
  else if (decimal == 3)
    decimal_multiplier = 1000.0;
  else if (decimal == 4)
    decimal_multiplier = 10000.0;
  else if (decimal == 5)
    decimal_multiplier = 100000.0;

  value = value / decimal_multiplier; // Set the decimal point

  // Ensure reading is in millimeters
  if (units == 1)
    value = value * 25.4; // Converts in reading to mm

  // Find and apply sign of reading
  if (sign == 8)
    value = -value; // Negative sign case

  return value;

} // indicatorReadMM()