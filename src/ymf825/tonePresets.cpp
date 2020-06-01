#include "tonePresets.h"

const uint8_t YMF825TonePresets::Default[YMF825_TONE_SIZE] = {
  0x01, 0x85,                                // Entire Tone Setting
  0x00, 0x7f, 0xf4, 0xbb, 0x00, 0x10, 0x40,  // Operator1 Setting
  0x00, 0xaf, 0xa0, 0x0e, 0x03, 0x10, 0x40,  // Operator2 Setting
  0x00, 0x2f, 0xf3, 0x9b, 0x00, 0x20, 0x41,  // Operator3 Setting
  0x00, 0xaf, 0xa0, 0x0e, 0x01, 0x10, 0x40,  // Operator4 Setting
};

const uint8_t YMF825TonePresets::Sine[YMF825_TONE_SIZE] = {
  0x01, 0x01,                                // Entire Tone Setting
  0x10, 0x81, 0x81, 0x00, 0x00, 0x10, 0x00,  // Operator1 Setting
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Operator2 Setting
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Operator3 Setting
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Operator4 Setting
};

const uint8_t YMF825TonePresets::Square[YMF825_TONE_SIZE] = {
  0x01, 0x01,                                // Entire Tone Setting
  0x10, 0x81, 0x81, 0x00, 0x00, 0x10, 0x30,  // Operator1 Setting
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Operator2 Setting
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Operator3 Setting
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Operator4 Setting
};

const uint8_t YMF825TonePresets::Triangle[YMF825_TONE_SIZE] = {
  0x01, 0x01,                                // Entire Tone Setting
  0x10, 0x81, 0x81, 0x00, 0x00, 0x10, 0x80,  // Operator1 Setting
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Operator2 Setting
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Operator3 Setting
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Operator4 Setting
};

const uint8_t YMF825TonePresets::Sawtooth[YMF825_TONE_SIZE] = {
  0x01, 0x01,                                // Entire Tone Setting
  0x10, 0x81, 0x81, 0x00, 0x00, 0x10, 0xc0,  // Operator1 Setting
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Operator2 Setting
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Operator3 Setting
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Operator4 Setting
};