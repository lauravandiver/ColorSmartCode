#include"hopperStepper.h"

void setup()
{
    hoppersInit();
}

long int ms = 0;

void loop()
{
  runHoppers(0x01);
}