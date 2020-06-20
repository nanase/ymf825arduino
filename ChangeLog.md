## 1.0.1

- Added a README.
- Added a change log.
- Added defines and reduced magic numbers.
  - `YMF825_VOICE_COUNT`, `YMF825_TONE_SIZE`, `YMF825_TONE_COUNT`, `YMF825_OPERATOR_SIZE`, `YMF825_OPERATOR_COUNT`, `YMF825_EQUALIZER_BAND_COUNT`, `YMF825_EQUALIZER_BAND_SIZE`
- Added examples.
  - stereo_tone.ino
- Added a macro `opAssignment` in toneParameter.cpp. This macro is used to simplify writing assignment to specified operator.
- Replaced for-loop to `memcpy`.

## 1.0 (2020/06/11)

- Published first version.
