#include "ymf825/driver.h"

#define opAddress(operatorNumber, offset) (operatorNumber * YMF825_OPERATOR_SIZE + 2 + offset)
#define opAssignment(address, mask, value) (memory[address] = (memory[address] & mask) | (value))

ToneParameter::ToneParameter() {}

ToneParameter::ToneParameter(const uint8_t *source) {
  fillMemory(source);
}

void ToneParameter::fillMemory(const uint8_t *source) {
  memcpy(memory, source, YMF825_TONE_SIZE);
}

uint8_t ToneParameter::getBaseOctave() {
  return memory[0] & 0b00000011;
}

void ToneParameter::setBaseOctave(uint8_t value) {
  memory[0] = value & 0b00000011;
}

uint8_t ToneParameter::getLfoFrequency() {
  return memory[1] >> 6;
}

void ToneParameter::setLfoFrequency(uint8_t value) {
  opAssignment(1, 0b00000111, value << 6);
}

uint8_t ToneParameter::getAlgorithm() {
  return memory[1] & 0b00000111;
}

void ToneParameter::setAlgorithm(uint8_t value) {
  opAssignment(1, 0b11000000, value & 0b00000111);
}

uint8_t ToneParameter::getSustainRate(uint8_t operatorNumber) {
  return memory[opAddress(operatorNumber, 0)] >> 4;
}

void ToneParameter::setSustainRate(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 0), 0b00001001, value << 4);
}

bool ToneParameter::getIgnoreKeyOff(uint8_t operatorNumber) {
  return (memory[opAddress(operatorNumber, 0)] & 0b00001000) >> 3;
}

void ToneParameter::setIgnoreKeyOff(uint8_t operatorNumber, bool value) {
  opAssignment(opAddress(operatorNumber, 0), 0b11110001, value ? 0b00001000 : 0);
}

bool ToneParameter::getEnableKeyScaleSensitivity(uint8_t operatorNumber) {
  return memory[opAddress(operatorNumber, 0)] & 0b00000001;
}

void ToneParameter::setEnableKeyScaleSensitivity(uint8_t operatorNumber, bool value) {
  opAssignment(opAddress(operatorNumber, 0), 0b11111000, value ? 0b00000001 : 0);
}

uint8_t ToneParameter::getReleaseRate(uint8_t operatorNumber) {
  return memory[opAddress(operatorNumber, 1)] >> 4;
}

void ToneParameter::setReleaseRate(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 1), 0b00001111, value << 4);
}

uint8_t ToneParameter::getDecayRate(uint8_t operatorNumber) {
  return memory[opAddress(operatorNumber, 1)] & 0b00001111;
}

void ToneParameter::setDecayRate(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 1), 0b11110000, value & 0b00001111);
}

uint8_t ToneParameter::getAttackRate(uint8_t operatorNumber) {
  return memory[opAddress(operatorNumber, 2)] >> 4;
}

void ToneParameter::setAttackRate(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 2), 0b00001111, value << 4);
}

uint8_t ToneParameter::getSustainLevel(uint8_t operatorNumber) {
  return memory[opAddress(operatorNumber, 2)] & 0b00001111;
}

void ToneParameter::setSustainLevel(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 2), 0b11110000, value & 0b00001111);
}

uint8_t ToneParameter::getTotalLevel(uint8_t operatorNumber) {
  return memory[opAddress(operatorNumber, 3)] >> 2;
}

void ToneParameter::setTotalLevel(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 3), 0b00000011, value << 2);
}

uint8_t ToneParameter::getKeyScalingLevel(uint8_t operatorNumber) {
  return memory[opAddress(operatorNumber, 3)] & 0b00000011;
}

void ToneParameter::setKeyScalingLevel(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 3), 0b11111100, value & 0b00000011);
}

uint8_t ToneParameter::getAmplitudeModurationDepth(uint8_t operatorNumber) {
  return (memory[opAddress(operatorNumber, 4)] & 0b01100000) >> 5;
}

void ToneParameter::setAmplitudeModurationDepth(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 4), 0b00010111, (value & 0b00000011) << 5);
}

bool ToneParameter::getEnableAmplitudeModuration(uint8_t operatorNumber) {
  return (memory[opAddress(operatorNumber, 4)] & 0b00010000) >> 4;
}

void ToneParameter::setEnableAmplitudeModuration(uint8_t operatorNumber, bool value) {
  opAssignment(opAddress(operatorNumber, 4), 0b01100111, value ? 0b00010000 : 0);
}

uint8_t ToneParameter::getVibrationDepth(uint8_t operatorNumber) {
  return (memory[opAddress(operatorNumber, 4)] & 0b00000110) >> 1;
}

void ToneParameter::setVibrationDepth(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 4), 0b01110001, (value & 0b00000011) << 1);
}

bool ToneParameter::getEnableVibration(uint8_t operatorNumber) {
  return (memory[opAddress(operatorNumber, 4)] & 0b00000001);
}

void ToneParameter::setEnableVibration(uint8_t operatorNumber, bool value) {
  opAssignment(opAddress(operatorNumber, 4), 0b01110110, value ? 0b00000001 : 0);
}

uint8_t ToneParameter::getMagnificationOfFrequency(uint8_t operatorNumber) {
  return (memory[opAddress(operatorNumber, 5)] >> 4);
}

void ToneParameter::setMagnificationOfFrequency(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 5), 0b00000111, value << 4);
}

uint8_t ToneParameter::getDetune(uint8_t operatorNumber) {
  return (memory[opAddress(operatorNumber, 5)] & 0b00000111);
}

void ToneParameter::setDetune(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 5), 0b11110000, value & 0b00000111);
}

uint8_t ToneParameter::getWaveShape(uint8_t operatorNumber) {
  return (memory[opAddress(operatorNumber, 6)] >> 3);
}

void ToneParameter::setWaveShape(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 6), 0b00000111, value << 3);
}

uint8_t ToneParameter::getFeedbackLevel(uint8_t operatorNumber) {
  return (memory[opAddress(operatorNumber, 6)] & 0b00000111);
}

void ToneParameter::setFeedbackLevel(uint8_t operatorNumber, uint8_t value) {
  opAssignment(opAddress(operatorNumber, 6), 0b11111000, value & 0b00000111);
}

void ToneParameters::setParameter(uint8_t toneNumber, ToneParameter *parameter) {
  parameters[toneNumber] = *parameter;
}

void ToneParameters::setParameter(uint8_t toneNumber, const uint8_t *buffer) {
  parameters[toneNumber].fillMemory(buffer);
}

ToneParameter *ToneParameters::getParameter(uint8_t toneNumber) {
  return &(parameters[toneNumber]);
}
