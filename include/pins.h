#pragma once

#define h1_STEP 52
#define h1_DIR 46

#define h2_STEP 53
#define h2_DIR 48

#define h3_STEP 28
#define h3_DIR 50

#define h4_STEP 33
#define h4_DIR 29

#define h5_STEP 32
#define h5_DIR 30

#define h6_STEP 26
#define h6_DIR 23

#define ALIGN_STEP_PIN 38
#define ALIGN_DIR_PIN 40
#define ALIGN_EN_PIN 51
#define AL_CS_PIN 41
#define AL_SW_MOSI 37
#define AL_SW_MISO 39
#define AL_SW_SCK 35
#define AL_DIAG1 27

#define PULL_STEP_PIN 36
#define PULL_DIR_PIN 42
#define PULL_EN_PIN 49
#define PU_CS_PIN 43
#define PU_SW_MOSI 37
#define PU_SW_MISO 39
#define PU_SW_SCK 35

#define WIND_STEP_PIN 34
#define WIND_DIR_PIN 44
#define WIND_EN_PIN 47
#define W_CS_PIN 45
#define W_SW_MOSI 37
#define W_SW_MISO 39
#define W_SW_SCK 35

#define LCH1_DOUT_PIN 25
#define LCH1_SCK_PIN 24
#define LCH2_DOUT_PIN 34
#define LCH2_SCK_PIN 34
#define LCH3_DOUT_PIN 34
#define LCH3_SCK_PIN 34
#define LCH4_DOUT_PIN 34
#define LCH4_SCK_PIN 34
#define LCH5_DOUT_PIN 34
#define LCH5_SCK_PIN 34
#define LCH6_DOUT_PIN 34
#define LCH6_SCK_PIN 34

#define DIA_CLK_PIN 2
#define DIA_DATA_PIN 52
#define DIA_REQ_PIN 50

// Message Ready pin bewteen pi and arduino
#define PI2A_MSG_RDY_PIN 20

#define thermoDO1 49
#define thermoDO2 50
#define thermoDO3 51
#define thermoCLK 52
#define thermoCS 53

#define relay_1 23 // heaterband 1
#define relay_2 25 // heaterband 2
#define relay_3 27 // heaterband 3
#define relay_4 29 // fans

//Shredder Pins
#define SHRED_DIR 25          // Digital pin for direction of motor
#define SHRED_PWM 3          // Shredder motor PWM driving signal
#define SHRED_SAFETY 7        // Shredder safety switch

//Extruder Pins
#define EXTR_DIR 24          // Direction pin for the extruder motor
#define EXTR_PWM 5           // Extruder motor PWM driving signal
