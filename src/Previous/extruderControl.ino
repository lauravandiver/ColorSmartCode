// Set up thermocouples

#include "max6675.h"
#include "pins.h"

//int thermoDO1 = 49;
//int thermoDO2 = 50;
//int thermoDO3 = 51;
//int thermoCLK = 52;
//int thermoCS = 53;

int destemp1 = 20;
int destemp2 = destemp1 - 40;
int destemp3 = destemp2 - 60;
int temp1 = 0;
int temp2 = 0;
int temp3 = 0;
int overshoot1 = 20;
int overshoot2 = 40;
int overshoot3 = 60;
int undershoot = 1;

bool done = 0;

MAX6675 thermocouple1(thermoCLK, thermoCS, thermoDO1);
MAX6675 thermocouple2(thermoCLK, thermoCS, thermoDO2);
MAX6675 thermocouple3(thermoCLK, thermoCS, thermoDO3);

// Set up heaterband relays

//int relay_1 = 23;   // heaterband 1
//int relay_2 = 25;   // heaterband 2
//int relay_3 = 27;   // heaterband 3
//int relay_4 = 29;   // fans

void setup() {
  Serial.begin(9600);

  //Serial.println("\nExtruder Test with one heaterband and thermocouple");
  //Serial.println("Heating Up");

  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  //pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);
 
  checktemps();
  fanControl(1);
  startExtruder();

  // wait for MAX chip to stabilize
  delay(500);  // was 500
}

void loop() {
  if(done){
    extrudOff();
    fanControl(0);
  }
  else{
    adjusttemps();
  }
  
  // wait for the MAX6675 update
  delay(5000);
  Serial.println();
}

void startExtruder() {
  while (temp1 <(destemp1 - overshoot1)){
    digitalWrite(relay_1, LOW);
    //checktemps();
  }
  Serial.println("Section 1 warmed up");
  checktemps();

  while (temp2 <(destemp2 - overshoot2)){
    digitalWrite(relay_2, LOW);
    //checktemps();
  }
  Serial.println("Section 2 warmed up");
  checktemps();

//  while (temp3 <(destemp3 - overshoot3)){
//    digitalWrite(relay_3, LOW);
//  }
//  Serial.println("Section 3 warmed up");
//  //checktemps();

}

void checktemps() {

  temp1 = thermocouple1.readCelsius();
  temp2 = thermocouple2.readCelsius();
  temp3 = thermocouple3.readCelsius();

  // print 3 temps
  Serial.print("C = "); 
  Serial.print(temp1);
  Serial.print(", ");
  Serial.print(temp2);
  Serial.print(", ");
  Serial.println(temp3);
}

void adjusttemps(){
  // Adjust temp1
  if (temp1 <= (destemp1 + undershoot)){
    digitalWrite(relay_1, LOW);
    Serial.println("Relay 1 ON");
  }
  else{
    digitalWrite(relay_1, HIGH);
    Serial.println("Relay 1 OFF");
  }

  // Adjust temp2
  if (temp2 <= (destemp2 + undershoot)){
    digitalWrite(relay_2, LOW);
    Serial.println("Relay 2 ON");
  }
  else{
    digitalWrite(relay_2, HIGH);
    Serial.println("Relay 2 OFF");
  }

  // Adjust temp3
//  if (temp3 <= (destemp3 + undershoot)){
//    digitalWrite(relay_3, LOW);
//    Serial.println("Relay 3 ON");
//  }
//  else{
//    digitalWrite(relay_3, HIGH);
//    Serial.println("Relay 3 OFF");
//  }
}

void fanControl(int state){
  if(state){
    digitalWrite(relay_2, LOW);
    Serial.println("Fans ON");
  }
  else{
    digitalWrite(relay_2, HIGH);
    Serial.println("Fans OFF");
  }
}

void extrudOff(){
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);
  Serial.println("All relays OFF");
}
