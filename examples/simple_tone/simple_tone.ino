#include "ymf825.h"
#include "ymf825/driver.h"
#include "ymf825/tonePresets.h"

#define PIN_RESET PIN_A6
#define PIN_SS PIN_A7

YMF825 ymf825(PIN_RESET, PIN_SS);
YMF825Driver driver(&ymf825);

void setup() {
  driver.initialize(YMF825_VOLTAGE_3V3);
  driver.setTone(YMF825TonePresets::Default);
}

void loop() {
  const uint8_t NOTES[] = {
    YMF825_NOTE_C, YMF825_NOTE_D, YMF825_NOTE_E, YMF825_NOTE_F,
    YMF825_NOTE_G, YMF825_NOTE_F, YMF825_NOTE_E, YMF825_NOTE_D,
  };

  for (uint8_t i = 0; i < sizeof(NOTES); i++) {
    driver.noteOff(0);
    delay(25);
    driver.noteOn(0, 4, NOTES[i]);  // Octave 4
    delay(475);
  }
}
