# pragma once
// Set up thermocouples

#include "MAX6675.h"

#define thermoDO1 49
#define thermoDO2 50
#define thermoDO3 51
#define thermoCLK 52
#define thermoCS 53
#define done = 0

// set up thermocouples
MAX6675 thermocouple1(thermoCLK, thermoCS, thermoDO1);
MAX6675 thermocouple2(thermoCLK, thermoCS, thermoDO2);
MAX6675 thermocouple3(thermoCLK, thermoCS, thermoDO3);

// Set up heaterband relays

#define relay_1 = 23   // heaterband 1
#define relay_2 = 25   // heaterband 2
#define relay_3 = 27   // heaterband 3
#define relay_4 = 29   // fans

int gettemp1() {
  return thermocouple1.readCelsius();
}

int gettemp2() {
  return thermocouple2.readCelsius();
}
int gettemp3() {
  return thermocouple3.readCelsius();
}

void startExtruder(int destemp) {
  static int destemp1 = destemp;
  static int destemp2 = destemp1 - 40;
  static int destemp3 = destemp2 - 60;

  static int overshoot1 = 20;
  static int overshoot2 = 40;
  static int overshoot3 = 60;

  while (gettemp1() <(destemp1 - overshoot1)){
    digitalWrite(relay_1, LOW);
  }
  while (gettemp2() <(destemp2 - overshoot2)){
    digitalWrite(relay_2, LOW);
    //checktemps();
  }
//  while (gettemp3() <(destemp3 - overshoot3)){
//    digitalWrite(relay_3, LOW);
//  }
}

void adjusttemps(int destemp){
  static int destemp1 = destemp;
  static int destemp2 = destemp1 - 40;
  static int destemp3 = destemp2 - 60;

  static int undershoot = 1;

  // Adjust temp1
  if (gettemp1() <= (destemp1 + undershoot)){
    digitalWrite(relay_1, LOW);
  }
  else{
    digitalWrite(relay_1, HIGH);
  }
  // Adjust temp2
  if (gettemp2() <= (destemp2 + undershoot)){
    digitalWrite(relay_2, LOW);
  }
  else{
    digitalWrite(relay_2, HIGH);
  }
  // Adjust temp3
//  if (gettemp3() <= (destemp3 + undershoot)){
//    digitalWrite(relay_3, LOW);
//  }
//  else{
//    digitalWrite(relay_3, HIGH);
//  }
}

void fanControl(int state){
  if(state){
    digitalWrite(relay_2, LOW);
  }
  else{
    digitalWrite(relay_2, HIGH);
  }
}

void extrudOff(){
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);
}
