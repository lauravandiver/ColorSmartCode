#include"hopperStepper.h"

void setup()
{
    
}

long int ms = 0;

void loop()
{
  #ifndef HOPP_INIT
      #define HOPP_INIT
      initHoppers();
  #endif
  runHoppers(0x01);
}