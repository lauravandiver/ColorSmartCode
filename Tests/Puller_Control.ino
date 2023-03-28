#include"puller.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
 
  pullerInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  pullerRunSpeed(1600);

  delay(10);

}
