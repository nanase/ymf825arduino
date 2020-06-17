#include "ymf825.h"
#include "ymf825/driver.h"
#include "ymf825/tonePresets.h"

#define PIN_RESET PIN_A0
#define PIN_SS_LCH PIN_A6
#define PIN_SS_RCH PIN_A7

YMF825 ymf825(PIN_RESET, PIN_SS_LCH, PIN_SS_RCH);
YMF825Driver driver(&ymf825);

void setup() {
  driver.initialize(YMF825_VOLTAGE_3V3);
  driver.setTone(YMF825TonePresets::Sine);
}

void loop() {
  const uint8_t NOTES[] = {
    YMF825_NOTE_C, YMF825_NOTE_D, YMF825_NOTE_E, YMF825_NOTE_F,
    YMF825_NOTE_G, YMF825_NOTE_F, YMF825_NOTE_E, YMF825_NOTE_D,
  };

  for (uint8_t i = 0; i < sizeof(NOTES); i++) {
    ymf825.setTargetChip(YMF825_TARGET_LCH);
    driver.noteOff(0);
    delay(100);

    driver.setVoiceVolume(0x0c);
    driver.noteOn(0, 4, NOTES[i]);  // Lch, Octave 4
    delay(50);

    ymf825.setTargetChip(YMF825_TARGET_RCH);
    driver.noteOff(0);
    delay(100);

    driver.setVoiceVolume(0x08);
    driver.noteOn(0, 4, NOTES[i]);  // Rch, Octave 4
    delay(250);
  }
}
