#include"aligner.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
 
  alignerInit();
}

bool al_home = false;
void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(al_home);
  if(!al_home){
    al_home = alignerHome();
  }
  else{
    alignerRun();
  }

}
