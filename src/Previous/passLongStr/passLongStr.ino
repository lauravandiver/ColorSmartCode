#include <Arduino.h>

// PI2A
String messageIn = "";
String sfr_mode = ""; // s for shred, r for recycle
String run_shredder =
    ""; // Shredder control (off = 0, on foward = 1, on reverse = 2)
String set_temperature =
    "";                 // Desired set point temperature (C) (three numbers)
String set_hopper = ""; // Hopper selection variable (one number)
// String run_aligner = "";   // do we still need this?

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
// String shred_status = ""; // do we still need this?

void setup() { Serial.begin(115200); }

void loop() {

  // RECEIVE DATA
  if (Serial.available() > 0) {
    messageIn = Serial.readStringUntil('\n');
    Serial.print("You sent me: ");
    Serial.println(messageIn);
    sfr_mode = messageIn[0];
    run_shredder = messageIn[1];
    set_temperature = messageIn[2] + messageIn[3] + messageIn[4];
    set_hopper = messageIn[5];
  }

  // sfr mode
  if (sfr_mode == "s") {
    Serial.println("Lets shred stuff"); // enable shredder
  } else if (sfr_mode == "r") {
    Serial.println("Lets recycle stuff"); // enable recycler
  } else {
    Serial.println("no shred nor recycle chosen"); // Idle
  }

  // shred status
  if (run_shredder == "0") {
    Serial.println("shredder off");
  } else if (run_shredder == "1") {
    Serial.println("shredder on");
  } else if (run_shredder == "2") {
    Serial.println("shredder reverse");
  } else {
    Serial.println(
        "shredder is confused"); // make this a command to turn off shredder
  }

  // update other variables that I don't have declared in this code:
  // destemp = set_temperaure;
  // hopper_select = set_hopper;

  delay(1000);

  // SEND DATA
  // GET LOADCELL AND TEMP DATA
  loadcell1 = "010";
  loadcell2 = "020";
  loadcell3 = "030";
  loadcell4 = "040";
  loadcell5 = "050";
  loadcell6 = "060";
  temp1 = "42";
  temp2 = "43";
  temp3 = "44";

  // PACKAGE AND SEND
  messageOut = loadcell1 + loadcell2 + loadcell3 + loadcell4 + loadcell5 +
               loadcell6 + temp1 + temp2 + temp3 + "\n";
  Serial.print(messageOut);
}