#include "aligner.h"
#include "digitalIndicator.h"
#include "fanControl.h"
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

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(extrdFan_relay, OUTPUT);
  pinMode(coolFan_relay, OUTPUT);
  pinMode(eboxFan_relay, OUTPUT);

  // Initalize subsystems
  // loadcellInit();
  // indicatorInit();
  // alignerInit();
  digitalWrite(LED_BUILTIN, LOW);
  hoppersInit();
  pullerInit();
  int fanstat[3] = {1, 1, 1};
  winderInit();
  fanControl(fanstat);
  shredInit();

  delay(100);

  // alignerHome();
}

float diameter;            // Filament diameter measurement
uint32_t last_time = 0;    // Previous time stamp
uint32_t ms = millis();    // Current time
uint16_t pull_speed = 500; // Puller speed to be set
uint16_t wind_speed = 100; // Winder speed to be set
Pi2A inputCmd;             // Command structure recieved from Pi
A2Pi outReport;            // Report structure to be sent to Pi

uint8_t hopper = 0b00000001;

uint32_t tlast_time = 0;
uint32_t tms = millis();

void loop() {

  runHoppers(hopper);
  // Serial.println(hopper, BIN);

  tms = millis();
  if (tms - tlast_time > 5000) {
    hopper = hopper << 1;
    tlast_time = tms;
    if (hopper >= 0b01000000)
      hopper = 0b00000001;
  }

  // alignerRun();
  // winderRunSpeed(1000);
  // pullerRunSpeed(5000);
  // bool safe = runShred();
  // Serial.println(safe);
  //  startExtruder(60);
}
