#include "aligner.h"
#include "digitalIndicator.h"
#include "extruderMotor.h"
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
  while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(extrdFan_relay, OUTPUT);
  pinMode(coolFan_relay, OUTPUT);
  pinMode(eboxFan_relay, OUTPUT);

  // Initalize subsystems
  loadcellInit();
  tempInit();
  indicatorInit();
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
uint16_t pull_speed = 500; // Puller speed to be set
uint16_t wind_speed = 100; // Winder speed to be set
bool temp_ready = false;
bool safe;
int run_shred = 0;
int destemp = 0;
uint8_t hopper = 0b00000000;
uint32_t tlast_time = 0;
uint32_t last_time = 0;
uint32_t tms = millis();

void loop() {

  if (Serial.available() > 0) {
    messageIn = Serial.readStringUntil('\n');
    // Serial.print("You sent me: ");
    // Serial.println(messageIn);
    sfr_mode = messageIn[0];
    run_shredder = messageIn[1];
    set_temperature = messageIn[2] + messageIn[3] + messageIn[4];
    set_hopper = messageIn[5] + messageIn[6] + messageIn[7] + messageIn[8] + messageIn[9] + messageIn[10];
    // Serial.println(set_hopper);  // these serial.print statements aren't working
  }

  if (sfr_mode == "s") {
    // shred status
    if (run_shredder == "0") {
      // Serial.println("shredder off");
      run_shred = 0;
    } else if (run_shredder == "1") {
      // Serial.println("shredder on");
      run_shred = 1;
    } else if (run_shredder == "2") {
      // Serial.println("shredder reverse");
      run_shred = 2;
    } else {
      //Serial.println("shredder is confused"); // make this a command to turn
      // off shredder
    }

    if (run_shred == 1) {
      runShred();
    } else if (run_shred == 0) {
      shredStop();
    } else if (run_shred == 2) {
      reverseShred();
    }

  }
  else if (sfr_mode == "r") {
    // set destemp
    if (set_temperature == "160") {
      destemp = 160;
    } else if (set_temperature == "170") {
      destemp = 170;
    } else if (set_temperature == "180") {
      destemp = 180;
    } else if (set_temperature == "190") {
      destemp = 190;
    }

    // set hopper
    if (set_hopper == "000001"){
      hopper = 0b00001001;
    } else if (set_hopper == "000010"){
      hopper = 0b00001010;      
    } else if (set_hopper == "000100"){
      hopper = 0b00001100;   
    } else if (set_hopper == "010000"){
      hopper = 0b00011000;
    } else if (set_hopper == "100000"){
      hopper = 0b00101000;
    } else if (set_hopper == "001000") {
      hopper = 0b00001000;
    }

    alignerRun();
    winderRunSpeed(500);
    pullerRunSpeed(2000);
    // runHoppers(0b00111111);
    if (temp_ready == false) {
      temp_ready = startExtruder(destemp);
      runHoppers(hopper);
      //runHoppers(0b00111111);
      extrudeStop();
    } else {
      adjusttemps(destemp);
      runHoppers(hopper);
      // runHoppers(0b00111111);
      extrudeRun();
    }
  }

  //tms = millis();
  // if (tms - tlast_time > 30000) {
  //   diameter = indicatorReadMM();
  //   if (diameter > 0.05 && pull_speed < PU_MAX_V) {
  //     pull_speed += 100;
  //   } else if (diameter < 0.05 && pull_speed > PU_MIN_V) {
  //     pull_speed -= 100;
  //   }

  //   tlast_time = tms;
  // }

  // if (tms - last_time > 1500) {
  //   Serial.print("Loadcell 1: ");
  //   last_time = tms;
  //   if (lcH1.is_ready()) {
  //     Serial.println(readLoadCell(1));
  //   } else {
  //     Serial.println("Unreachable");
  //   }
  // }

  // if (Serial.available() == 1) {
  //   if (Serial.read() == 't') {
  //   }
  // }

  // if(tms-tlast_time > 10000){
  //   hopper = hopper<<1;
  //   tlast_time = tms;
  //   if(hopper > 0b00100000){
  //     hopper = 0b00000001;
  //   }
  // }

  // alignerRun();
  // winderRunSpeed(500);
  // pullerRunSpeed(2000);

  // if (temp_ready == false) {
  //   temp_ready = startExtruder(160);
  //   runHoppers(0b00000000);
  //   extrudeStop();
  // } else {
  //   adjusttemps(160);
  //   runHoppers(0b00000000);
  //   extrudeRun();
  // }

  // if (tms - last_time > 5000) {
  //   if (temp_ready) {
  //     Serial.print("A");
  //   }
  //   Serial.print("Zone 1: ");
  //   Serial.print(gettemp1());
  //   Serial.print("C;  Zone 2: ");
  //   Serial.print(gettemp2());
  //   Serial.print("C;  Zone 3: ");
  //   Serial.print(gettemp3());
  //   Serial.println("C;");
  //   Serial.println();
  //   Serial.print(digitalRead(HB1_relay));
  //   Serial.print("  ");
  //   Serial.print(digitalRead(HB2_relay));
  //   Serial.print("  ");
  //   Serial.println(digitalRead(HB3_relay));

  //   // Serial.println();
  //   // //Serial.println(lcH5.read_average(3));
  //   // Serial.print("Loadcell Values: ");
  //   // Serial.print(readLoadCell(1));
  //   // Serial.print("  ");
  //   // Serial.print(readLoadCell(2));
  //   // Serial.print("  ");
  //   // Serial.print(readLoadCell(3));
  //   // Serial.print("  ");
  //   // Serial.print(readLoadCell(4));
  //   // Serial.print("  ");
  //   // Serial.print(readLoadCell(5));
  //   // Serial.print("  ");
  //   // Serial.println(readLoadCell(6));

  //   // Serial.println();
  //   // Serial.print("Diameter: ");
  //   // Serial.print(indicatorReadMM(), 3);
  //   // Serial.println(" mm");
  //   // Serial.println();
  //   tlast_time = tms;
  // }
}
