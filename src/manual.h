#include "aligner.h"
#include "digitalIndicator.h"
#include "hopperStepper.h"
#include "loadcell.h"
#include "puller.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("Begin");
  Serial.println("Press r to read or t to tare or d to read diameter");
  Serial.println();

  loadcellInit();
  indicatorInit();
}

int weight;

void loop() {
  delay(500);

  if (Serial.available()) {
    char temp = Serial.read();
    Serial.println(temp);
    Serial.println();

    if (temp == 'r') {
      weight = readLoadCell(4);
      Serial.print("Reading: ");
      Serial.print(weight);
      Serial.print(" grams");
      Serial.println();
      Serial.println("Press r to read or t to tare");
    }

    else if (temp == 't') {
      Serial.print("Previous Zero Factor: ");
      Serial.print(zero_factor);
      Serial.println();
      // Serial.println(millis());

      loadcellTare();

      // Serial.println(millis());
      Serial.print("New Zero Factor: ");
      Serial.print(zero_factor);
      Serial.println();
      Serial.println("Press r to read or t to tare");
    }

    else if (temp == 'd') {
      Serial.print("Diameter Reading: ");
      float x = indicatorReadMM();
      Serial.println(x, 3);
      
      Serial.println();
      Serial.println("Press r to read or t to tare or d to read diameter");
    }
  }
}