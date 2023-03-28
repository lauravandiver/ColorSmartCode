#include"winder.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
 
  windInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  winderRunSpeed(1600);

  delay(10);

}