/* piArduinoComm.h
 * Nikolas Prochaska
 * For ColorSmart SFR
 * Arduino side data structures and functions used for communicating
 * data between the Arduino and Raspberry Pi
 */

#pragma once

#include <Arduino.h>

// PI2A
String messageIn = "";
String sfr_mode = ""; // s for shred, r for recycle
String run_shredder =
    ""; // Shredder control (off = 0, on foward = 1, on reverse = 2)
String set_temperature1 = "";
String set_temperature2 = "";
String set_temperature3 = "";
String set_temperature =
    "";                 // Desired set point temperature (C) (three numbers)
String set_hopper1 = "";
String set_hopper2 = "";
String set_hopper3 = "";
String set_hopper4 = "";
String set_hopper5 = "";
String set_hopper6 = "";
String set_hopper = ""; // Hopper selection variable (one number)

// A2PI
String messageOut = "";
String loadcell1 = ""; // Values of load cells (g) (three numbers)
String loadcell2 = ""; // Values of load cells (g) (three numbers)
String loadcell3 = ""; // Values of load cells (g) (three numbers)
String loadcell4 = ""; // Values of load cells (g) (three numbers)
String loadcell5 = ""; // Values of load cells (g) (three numbers)
String loadcell6 = ""; // Values of load cells (g) (three numbers)
String temp1 = "";     // Values from thermocouples (C) (three numbers)
String temp2 = "";     // Values from thermocouples (C) (three numbers)
String temp3 = "";     // Values from thermocouples (C) (three numbers)