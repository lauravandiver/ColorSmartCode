#include <Arduino.h>
#include"aligner.h"
#include"hopperStepper.h"
#include"loadcell.h"
#include"puller.h"

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Begin");
  Serial.println("Press r to read or t to tare");
  Serial.println();

  loadcellInit();
}

int weight;

void loop() {
  delay(500);

  if(Serial.available()){
    char temp = Serial.read();
    Serial.println(temp);
    Serial.println();

    if(temp == 'r'){
      weight = readLoadCell(1);
      Serial.print("Reading: ");
      Serial.print(weight);
      Serial.print(" grams");
      Serial.println();
      Serial.println("Press r to read or t to tare");
    }

    else if(temp == 't'){
      Serial.print("Previous Zero Factor: ");
      Serial.print(zero_factor);
      Serial.println();
      //Serial.println(millis());

      loadcellTare();
      
      //Serial.println(millis());
      Serial.print("New Zero Factor: ");
      Serial.print(zero_factor);
      Serial.println();
      Serial.println("Press r to read or t to tare");
    }
  }

}