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
#include "extruderMotor.h"
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
  //loadcellInit();
  tempInit();
  // indicatorInit();
  alignerInit();
  // digitalWrite(LED_BUILTIN, LOW);
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
bool temp_ready = false;

uint8_t hopper = 0b00000001;

uint32_t tlast_time = 0;
uint32_t tms = millis();

void loop() {

  

  tms = millis();
  // if(tms-tlast_time > 10000){
  //   hopper = hopper<<1;
  //   tlast_time = tms;
  //   if(hopper > 0b00100000){
  //     hopper = 0b00000001;
  //   }
  // }

  alignerRun();
  winderRunSpeed(1000);
  pullerRunSpeed(5000);
  // bool safe = runShred();

  if (temp_ready == false) {
    temp_ready = startExtruder(190);
    runHoppers(0b00000000);
    extrudeStop();
  } else {
    adjusttemps(190);
    runHoppers(0b00000000);
    extrudeRun();
  }

  //int t1 = thermocouple1.readCelsius();

  if (tms - tlast_time > 1000) {
    if(temp_ready){Serial.print("A");}
    Serial.print("Zone 1: ");
    Serial.print(gettemp1());
    Serial.print("C;  Zone 2: ");
    Serial.print(gettemp2());
    Serial.print("C;  Zone 3: ");
    Serial.print(gettemp3());
    Serial.println("C;");
    Serial.println();
    tlast_time = tms;
  }
}
