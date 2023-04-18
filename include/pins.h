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
#define h6_DIR 31

#define ALIGN_STEP_PIN 38
#define ALIGN_DIR_PIN 40
#define ALIGN_EN_PIN 51
#define AL_CS_PIN 41
#define AL_SW_MOSI 37
#define AL_SW_MISO 39
#define AL_SW_SCK 35
#define AL_DIAG1 27
#define AL_HOME_SW 27

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

// Thermocouple MAX Board Pins
#define thermoDO1 22
#define thermoDO2 23
#define thermoDO3 2
#define thermoCLK1 14
#define thermoCS1 15
#define thermoCLK2 16
#define thermoCS2 17
#define thermoCLK3 A14
#define thermoCS3 A10

// Heaterband Relay Pins
#define HB1_relay 9
#define HB2_relay 10
#define HB3_relay 11

// Fan Relay Pins
#define extrdFan_relay A0 // Filament cooling fan
#define coolFan_relay A8  // Extruder heatsink fan
#define eboxFan_relay A4  // Power case fan
// #define relay_4 29 // No connection

// Shredder Pins
#define SHRED_DIR 25   // Digital pin for direction of motor
#define SHRED_PWM 3    // Shredder motor PWM driving signal
#define SHRED_SAFETY 7 // Shredder safety switch

// Extruder Pins
#define EXTR_DIR 24 // Direction pin for the extruder motor
#define EXTR_PWM 5  // Extruder motor PWM driving signal
