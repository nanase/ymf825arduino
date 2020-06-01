#include "ymf825/driver.h"

const double fnumTable[12] = {
  // fnumTable[i] = getFnum(440.0 * pow(2.0, (48.0 + i - 69.0) / 12.0), 3);
  357.206105157084,    // A
  378.44668549375604,  // A#
  400.9502964632338,   // B
  424.7920417752144,   // C
  450.05149103837175,  // C#
  476.812945316528,    // D
  505.16571847561823,  // D#
  535.204435260415,    // E
  567.0293470958184,   // F
  600.7466666666667,   // F#
  636.4689223926988,   // G
  674.3153339816948,   // G#
};

YMF825Driver::YMF825Driver(YMF825Device *device) {
  this->device = device;
}

void YMF825Driver::setClockEnable(bool enable) {
  device->write(0x00, enable ? 0x01 : 0x00);
}

bool YMF825Driver::getClockEnable(uint8_t targetChip) {
  return device->read(targetChip, 0x00) == 0x01;
}

void YMF825Driver::setAllRegisterReset(bool state) {
  device->write(0x01, state ? 0x80 : 0x00);
}

bool YMF825Driver::getAllRegisterReset(uint8_t targetChip) {
  return device->read(targetChip, 0x01) == 0x80;
}

void YMF825Driver::setAnalogBlockPowerDown(uint8_t block) {
  device->write(0x02, block & 0x0f);
}

uint8_t YMF825Driver::getAnalogBlockPowerDown(uint8_t targetChip) {
  return device->read(targetChip, 0x02) & 0x0f;
}

void YMF825Driver::setGain(uint8_t gainLevel) {
  device->write(0x03, gainLevel & 0x03);
}

uint8_t YMF825Driver::getGain(uint8_t targetChip) {
  return device->read(targetChip, 0x03) & 0x03;
}

uint8_t YMF825Driver::getHardwareId(uint8_t targetChip) {
  return device->read(targetChip, 0x04) & 0x03;
}

void YMF825Driver::setToneParameters(ToneParameters *params, uint8_t *buffer) {
  buffer[0] = 0x80 + 16;

  for (uint8_t i = 0; i < 16; i++) {
    ToneParameter *toneParameter = params->getParameter(i);
    memcpy(buffer + YMF825_TONE_SIZE * i + 1, toneParameter->memory, YMF825_TONE_SIZE);
  }

  buffer[YMF825_TONE_SIZE * 16 + 1] = 0x80;
  buffer[YMF825_TONE_SIZE * 16 + 2] = 0x03;
  buffer[YMF825_TONE_SIZE * 16 + 3] = 0x81;
  buffer[YMF825_TONE_SIZE * 16 + 4] = 0x80;

  setToneParameter(buffer, YMF825_TONE_SIZE * 16 + 5);
}

void YMF825Driver::setToneParameter(ToneParameter *param) {
  uint8_t buffer[YMF825_TONE_SIZE + 5];

  buffer[0] = 0x81;

  for (uint8_t i = 0; i < YMF825_TONE_SIZE; i++) buffer[i + 1] = (*param).memory[i];

  buffer[YMF825_TONE_SIZE + 1] = 0x80;
  buffer[YMF825_TONE_SIZE + 2] = 0x03;
  buffer[YMF825_TONE_SIZE + 3] = 0x81;
  buffer[YMF825_TONE_SIZE + 4] = 0x80;

  setToneParameter(buffer, sizeof(buffer));
}

void YMF825Driver::setToneParameter(const uint8_t *preset) {
  ToneParameter toneParameter(preset);
  setToneParameter(&toneParameter);
}

void YMF825Driver::setToneParameter(uint8_t *data, uint16_t size) {
  device->burstwrite(0x07, data, size);
}

void YMF825Driver::setSequencerSetting(uint8_t sequencerSetting) {
  device->write(0x08, sequencerSetting);
}

uint8_t YMF825Driver::getSequencerSetting(uint8_t targetChip) {
  return device->read(targetChip, 0x08);
}

void YMF825Driver::setSequencerVolume(uint8_t volume, bool applyInterpolation, uint16_t size) {
  volume &= 0x1f;
  size &= 0x01ff;
  device->write(0x09, (uint8_t)(volume << 3 | (applyInterpolation ? 0x00 : 0x04) | size >> 8));
  device->write(0x0a, (uint8_t)(size & 0xff));
}

void YMF825Driver::getSequencerVolume(uint8_t targetChip, uint8_t *volume, bool *applyInterpolation, uint16_t *size) {
  uint8_t msb = device->read(targetChip, 0x09);
  uint8_t lsb = device->read(targetChip, 0x0a);

  *volume             = msb >> 3;
  *applyInterpolation = (msb & 0x04) == 0;
  *size               = ((uint16_t)msb & 0x01) << 8 | lsb;
}

void YMF825Driver::setVoiceNumber(uint8_t number) {
  device->write(0x0b, number & 0x0f);
}

uint8_t YMF825Driver::getVoiceNumber(uint8_t targetChip) {
  return device->read(targetChip, 0x0b) & 0x0f;
}

void YMF825Driver::setVoiceVolume(uint8_t volume) {
  device->write(0x0c, (volume & 0x1f) << 2);
}

void YMF825Driver::setFnumAndBlock(uint16_t fnum, uint8_t block) {
  fnum &= 0x03ff;
  block &= 0x07;

  device->write(0x0d, ((fnum & 0x0380) >> 4) | (block & 0x07));
  device->write(0x0e, fnum & 0x7f);
}

void YMF825Driver::setToneFlag(uint8_t toneNumber, bool keyOn, bool mute, bool resetEnvelopeGenerator) {
  device->write(0x0f, ((keyOn ? 0x40 : 0x00) | (mute ? 0x20 : 0x00) | (resetEnvelopeGenerator ? 0x10 : 0x00) |
                       toneNumber & 0x0f));
}

void YMF825Driver::setChannelVolume(uint8_t volume, bool applyInterpolation) {
  device->write(0x10, (volume & 0x1f) << 2 | (applyInterpolation ? 0x00 : 0x01));
}

void YMF825Driver::setVibrationModuration(uint8_t depth) {
  device->write(0x11, depth & 0x07);
}

void YMF825Driver::setFrequencyMultiplier(uint8_t integer, uint16_t fraction) {
  fraction &= 0x01ff;
  device->write(0x12, (uint8_t)((integer & 0x03) << 3 | fraction >> 6));
  device->write(0x13, (uint8_t)((fraction & 0x3f) << 1));
}

void YMF825Driver::setInterporationInMuteState(bool enable) {
  device->write(0x14, enable ? 0x00 : 0x01);
}

void YMF825Driver::setSequencerTimeUnitSetting(uint16_t timeUnit) {
  timeUnit &= 0x3fff;
  device->write(0x17, (uint8_t)(timeUnit >> 7));
  device->write(0x18, (uint8_t)(timeUnit & 0x7f));
}

void YMF825Driver::setMasterVolume(uint8_t volume) {
  device->write(0x19, (uint8_t)((volume & 0x3f) << 2));
}

uint8_t YMF825Driver::getMasterVolume(uint8_t targetChip) {
  return device->read(targetChip, 0x19) >> 2;
}

void YMF825Driver::setSoftResetFlag(uint8_t value) {
  device->write(0x1a, value);
}

uint8_t YMF825Driver::getSoftResetFlag(uint8_t targetChip) {
  return device->read(targetChip, 0x1a);
}

void YMF825Driver::setVolumeInterpolationSetting(bool dadjt, uint8_t muteItime, uint8_t chvolItime, uint8_t mvolItime) {
  device->write(0x1b,
                ((dadjt ? 0x40 : 0x00) | ((muteItime & 0x03) << 4) | ((chvolItime & 0x03) << 2) | (mvolItime & 0x03)));
}

void YMF825Driver::getVolumeInterpolationSetting(uint8_t targetChip, bool *dadjt, uint8_t *muteItime,
                                                 uint8_t *chvolItime, uint8_t *mvolItime) {
  uint8_t readByte = device->read(targetChip, 0x1b);
  *dadjt           = (readByte & 0x40) != 0;
  *muteItime       = (readByte >> 4) & 0x03;
  *chvolItime      = (readByte >> 2) & 0x03;
  *mvolItime       = readByte & 0x03;
}

void YMF825Driver::setLfoResetFlag(bool reset) {
  device->write(0x1c, reset ? 0x01 : 0x00);
}

bool YMF825Driver::getLfoResetFlag(uint8_t targetChip) {
  return device->read(targetChip, 0x1c) == 0x01;
}

void YMF825Driver::setPowerRailSelection(uint8_t voltage) {
  device->write(0x1d, voltage & 0x01);
}

uint8_t YMF825Driver::getPowerRailSelection(uint8_t targetChip) {
  return device->read(targetChip, 0x1d) & 0x01;
}

void YMF825Driver::setEqualizer(uint8_t band, const double *coefficients) {
  uint8_t data[15];

  for (uint8_t i = 0; i < 5; i++) {
    uint32_t registerFormat = YMF825Driver::serializeCoefficient(coefficients[i]);

    data[i * 3 + 0] = (uint8_t)(registerFormat >> 16);
    data[i * 3 + 1] = (uint8_t)((registerFormat >> 8) & 0xff);
    data[i * 3 + 2] = (uint8_t)(registerFormat & 0xff);
  }

  device->burstwrite(0x20 + band, data, 15);
}

uint32_t YMF825Driver::getEqualizerCoefficient(uint8_t targetChip, uint8_t band, uint8_t coefficientNumber) {
  uint8_t baseAddress = 0x23 + band * 15 + coefficientNumber * 3;
  uint8_t byte0       = device->read(targetChip, baseAddress + 0);
  uint8_t byte1       = device->read(targetChip, baseAddress + 1);
  uint8_t byte2       = device->read(targetChip, baseAddress + 2);
  return (byte0 << 16) + (byte1 << 8) + byte2;
}

void YMF825Driver::getEqualizer(uint8_t targetChip, uint8_t band, double *coefficients) {
  for (uint8_t i = 0; i < 5; i++)
    coefficients[i] = YMF825Driver::deserializeCoefficient(getEqualizerCoefficient(targetChip, band, i));
}

void YMF825Driver::setSoftwareTestCommunication(uint8_t value) {
  device->write(0x50, value);
}

uint8_t YMF825Driver::getSoftwareTestCommunication(uint8_t targetChip) {
  return device->read(targetChip, 0x50);
}

// Static Functions

double YMF825Driver::getFnum(double frequency, uint8_t block) {
  // Original Formula
  // const fnum = (freq * Math.pow(2, 19)) / (Math.pow(2, block - 1) * 48000);
  return pow(2.0, 13 - block) * frequency / 375.0;
}

double YMF825Driver::getFrequency(double fnum, uint8_t block) {
  // Original Formula
  // const freq = (48000 * Math.pow(2, block - 1) * fnum) / Math.pow(2, 19);
  return 375.0 * pow(2.0, block - 13) * fnum;
}

void YMF825Driver::getFnumAndBlock(uint8_t key, double *fnum, uint8_t *block, double *correction) {
  if (key < 0 || key > 127)
    key = 0;  // error

  double blockMod = 1.0;
  *block          = key / 12 - 2;

  if (*block < 0) {
    blockMod = pow(2.0, *block);
    *block   = 0;
  } else if (*block > 6) {
    blockMod = pow(2.0, *block - 6);
    *block   = 6;
  }

  *fnum            = fnumTable[key % 12] * blockMod;
  double idealFreq = getFrequency(*fnum, *block);

  if (*fnum > 1023.0)
    *fnum = 1023.0;

  *correction = idealFreq / getFrequency(round(*fnum), *block);
}

void YMF825Driver::getFraction(double multiplier, uint8_t *integer, uint16_t *fraction) {
  if (multiplier >= 4.0 || multiplier < 0.0)
    multiplier = 0.0;  // error

  multiplier = round(multiplier * 512.0);

  if (multiplier >= 4 * 512) {
    *integer  = 3;
    *fraction = 511;
  } else {
    *integer  = (uint8_t)(multiplier / 512.0);
    *fraction = (uint16_t)(multiplier - *integer * 512);
  }
}

uint32_t YMF825Driver::serializeCoefficient(double coefficient) {
  if (isnan(coefficient) || isinf(coefficient) || coefficient <= -8.0 || coefficient >= 8.0)
    coefficient = 0.0;  // error

  uint8_t integer   = (uint8_t)abs(coefficient);
  uint32_t fraction = (uint32_t)round(abs(coefficient - (uint8_t)coefficient) * 1048575.0);

  // 2'complement
  if (coefficient < 0.0) {
    integer  = 0x08 | (~integer & 0x07);
    fraction = ~fraction & 0x0fffff;
  }

  // Sign bit:       1 bit  (CEQ##[23])
  // Integer part:   3 bits (CEQ##[22:20]) -> 2'complement
  // Fraction part: 20 bits (CEQ##[19:0])  -> 2'complement
  return (integer << 20) | fraction;
}

double YMF825Driver::deserializeCoefficient(uint32_t registerFormat) {
  if (registerFormat >> 24 > 0)
    registerFormat = 0.0;  // error

  // value is negative when sign is true
  bool sign         = (registerFormat & 0x00800000) != 0;
  uint8_t integer   = (registerFormat & 0x00700000) >> 20;
  uint32_t fraction = registerFormat & 0x000fffff;

  // 2'complement
  if (sign) {
    integer  = ~integer & 0x07;
    fraction = ~fraction & 0x0fffff;
  }

  return (integer + fraction / 1048575.0) * (sign ? -1.0 : 1.0);
}

// High-level Functions

void YMF825Driver::initialize(uint8_t voltage) {
  device->initialize();
  device->setTargetChip(YMF825_TARGET_ALL);
  resetHardware();
  resetSoftware(voltage);

  for (uint8_t i = 0; i < 16; i++) {
    setVoiceNumber(i);
    setVoiceVolume(0x10);
  }
}

void YMF825Driver::resetHardware() {
  device->resetHardware();
}

void YMF825Driver::resetSoftware(uint8_t voltage) {
  setPowerRailSelection(voltage);
  setAnalogBlockPowerDown(0x0e);
  delay(1);
  setClockEnable(true);
  setAllRegisterReset(false);
  setSoftResetFlag(0xa3);
  delay(1);
  setSoftResetFlag(0x00);
  delay(30);
  setAnalogBlockPowerDown(0x04);
  delay(1);
  setAnalogBlockPowerDown(0x00);

  setMasterVolume(0x3c);
  setVolumeInterpolationSetting(false, 0x03, 0x03, 0x03);
  setInterporationInMuteState(true);
  setGain(0x01);

  setSequencerSetting(0xf6);
  delay(21);
  setSequencerSetting(0x00);
  setSequencerVolume(0x1f, true, 0x0000);

  setSequencerTimeUnitSetting(0x2000);
}

void YMF825Driver::setToneAssignment(uint8_t voice, uint8_t tone) {
  setVoiceNumber(voice);
  device->write(0x0f, toneFlag[voice] = (toneFlag[voice] & 0xf0) | (tone & 0x0f));
}

void YMF825Driver::noteOn(uint8_t voice, uint8_t key) {
  double fnum, correction;
  uint8_t block, integer;
  uint16_t fraction;

  getFnumAndBlock(key, &fnum, &block, &correction);
  getFraction(correction, &integer, &fraction);

  setVoiceNumber(voice);
  setFrequencyMultiplier(integer, fraction);
  setFnumAndBlock((uint16_t)fnum, block);
  device->write(0x0f, toneFlag[voice] |= 0b01000000);
}

void YMF825Driver::noteOn(uint8_t voice, int8_t octave, uint8_t key) {
  noteOn(voice, (octave + 2) * 12 + key - 3);
}

void YMF825Driver::noteOff(uint8_t voice) {
  setVoiceNumber(voice);
  device->write(0x0f, toneFlag[voice] &= 0b10111111);
}

void YMF825Driver::setTone(ToneParameters *params, uint8_t *buffer) {
  setSequencerSetting(0x16);
  setSequencerSetting(0x00);
  setToneParameters(params, buffer);
}

void YMF825Driver::setTone(ToneParameter *param) {
  setSequencerSetting(0x16);
  setSequencerSetting(0x00);
  setToneParameter(param);
}

void YMF825Driver::setTone(const uint8_t *preset) {
  setSequencerSetting(0x16);
  setSequencerSetting(0x00);
  setToneParameter(preset);
}

void YMF825Driver::setTone(uint8_t *data, uint16_t size) {
  setSequencerSetting(0x16);
  setSequencerSetting(0x00);
  setToneParameter(data, size);
}
