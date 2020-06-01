#pragma once

#include "Arduino.h"
#include "ymf825.h"

#define YMF825_TONE_SIZE 30

enum YMF825_VOLTAGE {
  YMF825_VOLTAGE_5V  = 0,
  YMF825_VOLTAGE_3V3 = 1,
};

enum YMF825_NOTE {
  YMF825_NOTE_A = 0,
  YMF825_NOTE_B = 2,
  YMF825_NOTE_C = 3,
  YMF825_NOTE_D = 5,
  YMF825_NOTE_E = 7,
  YMF825_NOTE_F = 8,
  YMF825_NOTE_G = 10,
};

class ToneParameter {
 public:
  uint8_t memory[YMF825_TONE_SIZE] = { 0 };

  ToneParameter();
  ToneParameter(const uint8_t *source);

  void fillMemory(const uint8_t *source);

  uint8_t getBaseOctave();
  void setBaseOctave(uint8_t value);
  uint8_t getLfoFrequency();
  void setLfoFrequency(uint8_t value);
  uint8_t getAlgorithm();
  void setAlgorithm(uint8_t value);

  uint8_t getSustainRate(uint8_t operatorNumber);
  void setSustainRate(uint8_t operatorNumber, uint8_t value);
  bool getIgnoreKeyOff(uint8_t operatorNumber);
  void setIgnoreKeyOff(uint8_t operatorNumber, bool value);
  bool getEnableKeyScaleSensitivity(uint8_t operatorNumber);
  void setEnableKeyScaleSensitivity(uint8_t operatorNumber, bool value);
  uint8_t getReleaseRate(uint8_t operatorNumber);
  void setReleaseRate(uint8_t operatorNumber, uint8_t value);
  uint8_t getDecayRate(uint8_t operatorNumber);
  void setDecayRate(uint8_t operatorNumber, uint8_t value);
  uint8_t getAttackRate(uint8_t operatorNumber);
  void setAttackRate(uint8_t operatorNumber, uint8_t value);
  uint8_t getSustainLevel(uint8_t operatorNumber);
  void setSustainLevel(uint8_t operatorNumber, uint8_t value);
  uint8_t getTotalLevel(uint8_t operatorNumber);
  void setTotalLevel(uint8_t operatorNumber, uint8_t value);
  uint8_t getKeyScalingLevel(uint8_t operatorNumber);
  void setKeyScalingLevel(uint8_t operatorNumber, uint8_t value);

  uint8_t getAmplitudeModurationDepth(uint8_t operatorNumber);
  void setAmplitudeModurationDepth(uint8_t operatorNumber, uint8_t value);
  bool getEnableAmplitudeModuration(uint8_t operatorNumber);
  void setEnableAmplitudeModuration(uint8_t operatorNumber, bool value);
  uint8_t getVibrationDepth(uint8_t operatorNumber);
  void setVibrationDepth(uint8_t operatorNumber, uint8_t value);
  bool getEnableVibration(uint8_t operatorNumber);
  void setEnableVibration(uint8_t operatorNumber, bool value);

  uint8_t getMagnificationOfFrequency(uint8_t operatorNumber);
  void setMagnificationOfFrequency(uint8_t operatorNumber, uint8_t value);
  uint8_t getDetune(uint8_t operatorNumber);
  void setDetune(uint8_t operatorNumber, uint8_t value);

  uint8_t getWaveShape(uint8_t operatorNumber);
  void setWaveShape(uint8_t operatorNumber, uint8_t value);
  uint8_t getFeedbackLevel(uint8_t operatorNumber);
  void setFeedbackLevel(uint8_t operatorNumber, uint8_t value);
};

class ToneParameters {
 public:
  ToneParameter parameters[16] = { ToneParameter() };

  void setParameter(uint8_t toneNumber, ToneParameter *parameter);
  void setParameter(uint8_t toneNumber, const uint8_t *buffer);
  ToneParameter *getParameter(uint8_t toneNumber);
};

class YMF825Driver {
 private:
  YMF825Device *device;
  uint8_t toneFlag[16] = { 0 };

 public:
  YMF825Driver(YMF825Device *device);

  // Low-level functions

  void setClockEnable(bool enable);
  bool getClockEnable(uint8_t targetChip);

  void setAllRegisterReset(bool state);
  bool getAllRegisterReset(uint8_t targetChip);

  void setAnalogBlockPowerDown(uint8_t block);
  uint8_t getAnalogBlockPowerDown(uint8_t targetChip);

  void setGain(uint8_t gainLevel);
  uint8_t getGain(uint8_t targetChip);

  uint8_t getHardwareId(uint8_t targetChip);

  void setToneParameters(ToneParameters *params, uint8_t *buffer);

  void setToneParameter(ToneParameter *param);
  void setToneParameter(const uint8_t *preset);
  void setToneParameter(uint8_t *data, uint16_t size);

  void setSequencerSetting(uint8_t sequencerSetting);
  uint8_t getSequencerSetting(uint8_t targetChip);

  void setSequencerVolume(uint8_t volume, bool applyInterpolation, uint16_t size);
  void getSequencerVolume(uint8_t targetChip, uint8_t *volume, bool *applyInterpolation, uint16_t *size);

  void setVoiceNumber(uint8_t number);
  uint8_t getVoiceNumber(uint8_t targetChip);

  void setVoiceVolume(uint8_t volume);

  void setFnumAndBlock(uint16_t fnum, uint8_t block);

  void setToneFlag(uint8_t toneNumber, bool keyOn, bool mute, bool resetEnvelopeGenerator);

  void setChannelVolume(uint8_t volume, bool applyInterpolation);

  void setVibrationModuration(uint8_t depth);

  void setFrequencyMultiplier(uint8_t integer, uint16_t fraction);

  void setInterporationInMuteState(bool enable);

  void setSequencerTimeUnitSetting(uint16_t timeUnit);

  void setMasterVolume(uint8_t volume);
  uint8_t getMasterVolume(uint8_t targetChip);

  void setSoftResetFlag(uint8_t value);
  uint8_t getSoftResetFlag(uint8_t targetChip);

  void setVolumeInterpolationSetting(bool dadjt, uint8_t muteItime, uint8_t chvolItime, uint8_t mvolItime);
  void getVolumeInterpolationSetting(uint8_t targetChip, bool *dadjt, uint8_t *muteItime, uint8_t *chvolItime,
                                     uint8_t *mvolItime);

  void setLfoResetFlag(bool reset);
  bool getLfoResetFlag(uint8_t targetChip);

  void setPowerRailSelection(uint8_t select);
  uint8_t getPowerRailSelection(uint8_t targetChip);

  void setEqualizer(uint8_t band, const double *coefficients);
  uint32_t getEqualizerCoefficient(uint8_t targetChip, uint8_t band, uint8_t coefficientNumber);
  void getEqualizer(uint8_t targetChip, uint8_t band, double *coefficients);

  void setSoftwareTestCommunication(uint8_t value);
  uint8_t getSoftwareTestCommunication(uint8_t targetChip);

  // Static Functions

  static double getFnum(double frequency, uint8_t block);
  static double getFrequency(double fnum, uint8_t block);
  static void getFnumAndBlock(uint8_t key, double *fnum, uint8_t *block, double *correction);
  static void getFraction(double multiplier, uint8_t *integer, uint16_t *fraction);

  static uint32_t serializeCoefficient(double coefficient);
  static double deserializeCoefficient(uint32_t registerFormat);

  // High-level Functions

  void resetHardware();
  void resetSoftware(uint8_t voltage);

  void initialize(uint8_t voltage);
  void setToneAssignment(uint8_t voice, uint8_t tone);

  void noteOn(uint8_t voice, uint8_t key);
  void noteOn(uint8_t voice, int8_t octave, uint8_t key);

  void noteOff(uint8_t voice);

  void setTone(ToneParameters *params, uint8_t *buffer);
  void setTone(ToneParameter *param);
  void setTone(const uint8_t *preset);
  void setTone(uint8_t *data, uint16_t size);
};
