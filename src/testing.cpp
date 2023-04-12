#include "aligner.h"
#include "digitalIndicator.h"
#include "hopperStepper.h"
#include "loadcell.h"
#include "piArduinoComm.h"
#include "puller.h"
#include "shredder.h"
#include "tempContol.h"
#include "winder.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  // Initalize subsystems
  // loadcellInit();
  // indicatorInit();
  alignerInit();
  hoppersInit();
  // pullerInit();
  // winderInit();
  shredInit();
  fanControl(1);
  shredInit();

  alignerHome();
  startExtruder(60);
}

float diameter;            // Filament diameter measurement
uint32_t last_time = 0;    // Previous time stamp
uint32_t ms = millis();    // Current time
uint16_t pull_speed = 500; // Puller speed to be set
uint16_t wind_speed = 100; // Winder speed to be set
Pi2A inputCmd;             // Command structure recieved from Pi
A2Pi outReport;            // Report structure to be sent to Pi

void loop() {

  //   if (digitalRead(PI2A_MSG_RDY_PIN)) {
  //     // Read in Pi's command data
  //     readSer2Struct(&inputCmd);
  //     // Send report to pi
  //     printStruct2Ser(outReport);
  //   }

  runHoppers(0b00111111);
  alignerRun();
  runShred();

  // pullerRunSpeed((uint16_t)inputCmd.puller_speed);
  // winderRunSpeed((uint16_t)inputCmd.winder_speed);

  // diameter = indicatorReadMM();

  //   for (int i; i < 6; i++) {
  //     outReport.loadcells[i] = readLoadCell(i);
  //   }

  // outReport.diameter = (int)(100 * diameter);
}
