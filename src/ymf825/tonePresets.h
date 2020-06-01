#pragma once

#include "driver.h"

class YMF825TonePresets {
 public:
  static const uint8_t Default[YMF825_TONE_SIZE];
  static const uint8_t Sine[YMF825_TONE_SIZE];
  static const uint8_t Square[YMF825_TONE_SIZE];
  static const uint8_t Triangle[YMF825_TONE_SIZE];
  static const uint8_t Sawtooth[YMF825_TONE_SIZE];
};
