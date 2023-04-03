#include "aligner.h"
#include "digitalIndicator.h"
#include "hopperStepper.h"
#include "loadcell.h"
#include "puller.h"
#include "winder.h"
#include <Arduino.h>

#define PRINT_DEL

typedef struct {
  int loadcells[6];
  int temperature[3];
  float diameter;
  bool shred_status;
} A2Pi;

typedef struct {
  int set_temperature[6];
  uint16_t puller_speed;
  uint16_t dummy;
  bool shred;
  bool run_winder;
  bool run_aligner;
} Pi2A;

void printStruct2Ser(A2Pi s) {
  for (int i = 0; i < sizeof(A2Pi); i++) {
    Serial.write(((unsigned char *)&s)[i]);
  }
}

bool readSer2Struct(Pi2A *s) {
  if (!Serial.available()) {
    return false;
  }
  for (int i = 0; i < sizeof(Pi2A); i++) {
    ((unsigned char *)s)[i] = (byte)Serial.read();
  }
  return true;
}

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("Begin");
  Serial.println();

  loadcellInit();
  indicatorInit();
  alignerInit();
  pullerInit();
  winderInit();

  alignerHome();

  Serial.println("Press any key to continue...");
  while (!Serial.available()) {
  }
  Serial.println(Serial.read());
  Serial.println();
  Serial.println("Press a/z to adjust puller,");
  Serial.println("Press s/x to adjust winder,");
  Serial.println("or press d to read the diameter");
}

int weight;
float diameter;
uint32_t last_time = 0;
uint32_t ms = millis();
uint16_t pull_speed = 500;
uint16_t wind_speed = 100;

void loop() {
  alignerRun();
  pullerRunSpeed(pull_speed);
  winderRunSpeed(wind_speed);
  diameter = indicatorReadMM();

  if (Serial.available()) {
    char temp = Serial.read();

    Serial.println();
    Serial.println("Old Values");
    Serial.print("Pull Speed: ");
    Serial.print(pull_speed);
    Serial.print("  Wind Speed: ");
    Serial.print(wind_speed);

    if (temp == 'a' && pull_speed < PU_MAX_V)
      pull_speed += 10;
    if (temp == 'z' && pull_speed > 10)
      pull_speed -= 10;
    if (temp == 's' && wind_speed < W_MAX_V)
      wind_speed += 10;
    if (temp == 'x' && wind_speed > 10)
      wind_speed -= 10;
    if (temp == 'd') {
      Serial.print("Diameter: ");
      Serial.println(diameter, 3);
    }

    Serial.println();
    Serial.println("New Values");
    Serial.print("Pull Speed: ");
    Serial.print(pull_speed);
    Serial.print("  Wind Speed: ");
    Serial.print(wind_speed);
    Serial.println();
  }
}
