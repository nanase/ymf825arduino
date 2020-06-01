#include "ymf825.h"
#include "ymf825/driver.h"
#include "ymf825/tonePresets.h"

#define PIN_RESET PIN_A6
#define PIN_SS PIN_A7

YMF825 ymf825(PIN_RESET, PIN_SS);
YMF825Driver driver(&ymf825);
ToneParameter toneParameter(YMF825TonePresets::Sine);

void setup() {
  driver.initialize(YMF825_VOLTAGE_3V3);
}

void loop() {
  const uint8_t NOTES[] = {
    YMF825_NOTE_C, YMF825_NOTE_D, YMF825_NOTE_E, YMF825_NOTE_F,
    YMF825_NOTE_G, YMF825_NOTE_F, YMF825_NOTE_E, YMF825_NOTE_D,
  };
  const uint8_t FEEDBACKS[] = { 0, 1, 2, 3, 4, 3, 2, 1 };

  for (uint8_t i = 0; i < sizeof(NOTES); i++) {
    driver.noteOff(0);
    delay(40);
    driver.noteOn(0, 4, NOTES[i]);  // Octave 4

    for (uint8_t j = 0; j < 8; j++) {
      toneParameter.setFeedbackLevel(0, FEEDBACKS[j]);
      driver.setTone(&toneParameter);
      delay(240);
    }
  }
}
