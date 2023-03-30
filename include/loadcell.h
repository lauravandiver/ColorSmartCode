/* loadcell.h
 * Nikolas Prochaska
 * For ColorSmart SFR
 * Definitions and constants for the operation of 
 * the loadcells used to weigh the material hoppers
 */

#pragma once

#include "pins.h"
#include<HX711.h>

HX711 lcH1;
HX711 lcH2;
HX711 lcH3;
HX711 lcH4;
HX711 lcH5;
HX711 lcH6;

#define CAL_FACT -705000
long zero_factor = 214715;

// Initalize loadcells and set their calibration factors and offsets
void loadcellInit(void){
    // Primary initialization and pin relations
    lcH1.begin(LCH1_DOUT_PIN, LCH1_SCK_PIN);
    lcH2.begin(LCH2_DOUT_PIN, LCH2_SCK_PIN);
    lcH3.begin(LCH3_DOUT_PIN, LCH3_SCK_PIN);
    lcH4.begin(LCH4_DOUT_PIN, LCH4_SCK_PIN);
    lcH5.begin(LCH5_DOUT_PIN, LCH5_SCK_PIN);
    lcH6.begin(LCH6_DOUT_PIN, LCH6_SCK_PIN);

    // Set calibration factor
    lcH1.set_scale(CAL_FACT);
    lcH2.set_scale(CAL_FACT);
    lcH3.set_scale(CAL_FACT);
    lcH4.set_scale(CAL_FACT);
    lcH5.set_scale(CAL_FACT);
    lcH6.set_scale(CAL_FACT);

    // "tare" the loadcells for hopper weight
    lcH1.set_offset(zero_factor);
    lcH2.set_offset(zero_factor);
    lcH3.set_offset(zero_factor);
    lcH4.set_offset(zero_factor);
    lcH5.set_offset(zero_factor);
    lcH6.set_offset(zero_factor);
    
} // loadcellInit

// Tare the loadcells by reading the avergae value across all
// hoppers and update zero_factor based on these readings
void loadcellTare(void){
    long tare1, tare2, tare3, tare4, tare5, tare6;
    tare1 = lcH1.read_average();
    tare2 = lcH2.read_average();
    tare3 = lcH3.read_average();
    tare4 = lcH4.read_average();
    tare5 = lcH5.read_average();
    tare6 = lcH6.read_average();

    zero_factor = tare1/6 + tare2/6 + tare3/6 + tare4/6 + tare5/6 + tare6/6;
    lcH1.set_offset(zero_factor);
    
} // loadcellInit

// Read a designated hopper and return the value in grams
int readLoadCell(int hopper){
    float reading = 0;
    int grams;

    switch (hopper)
    {
    case 1:
        reading = 1000*lcH1.get_units();
        break;
    case 2:
        reading = 1000*lcH2.get_units();
        break;
    case 3:
        reading = 1000*lcH3.get_units();
        break;
    case 4:
        reading = 1000*lcH4.get_units();
        break;
    case 5:
        reading = 1000*lcH5.get_units();
        break;
    case 6:
        reading = 1000*lcH6.get_units();
        break;
    default:
        break;
    } // switch hoppper

    grams = (int)reading;

    return grams;

} // read_loadcell
