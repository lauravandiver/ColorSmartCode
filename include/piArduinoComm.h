/* piArduinoComm.h
 * Nikolas Prochaska
 * For ColorSmart SFR
 * Arduino side data structures and functions used for communicating
 * data between the Arduino and Raspberry Pi
 */

#pragma once

#include <Arduino.h>

// Arduino to Pi data structure
typedef struct {
  int loadcells[6];   // Values of load cells (g)
  int temperature[3]; // Values from thermocouples (C)
  int diameter;       // Value read from indiactor (mm*100)
  bool shred_status;  // State of shredder safety
} A2Pi;

// Pi to Arduino data structure
typedef struct {
  int set_temperature; // Desired set point temperature (C)
  int puller_speed;    // Requested puller speed
  int winder_speed;    // Requested winder speed
  int hopper_select;   // Hopper selection variable
  int run_shredder;    // Shredder on/off
  int run_aligner;     // Aligner on/off
} Pi2A;

void printStruct2Ser(A2Pi s) {
  for (unsigned int i = 0; i < sizeof(A2Pi); i++) {
    Serial.write(((unsigned char *)&s)[i]);
  }
}

bool readSer2Struct(Pi2A *s) {
  if (!Serial.available()) {
    return false;
  }
  for (unsigned int i = 0; i < sizeof(Pi2A); i++) {
    ((unsigned char *)s)[i] = (byte)Serial.read();
  }
  return true;
}