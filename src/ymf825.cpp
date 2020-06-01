#include "ymf825.h"

#include "SPI.h"

const SPISettings spiSettings = SPISettings(YMF825_SPI_MAX_SPEED, MSBFIRST, SPI_MODE0);

YMF825::YMF825(uint8_t resetPin, uint8_t ssPin) {
  this->resetPin = resetPin;
  this->ssLchPin = ssPin;
  this->ssRchPin = ssPin;
  this->setTargetChip(YMF825_TARGET_MONO);
}

YMF825::YMF825(uint8_t resetPin, uint8_t ssLchPin, uint8_t ssRchPin) {
  this->resetPin = resetPin;
  this->ssLchPin = ssLchPin;
  this->ssRchPin = ssRchPin;
  this->setTargetChip(YMF825_TARGET_STEREO);
}

void YMF825::initialize() {
  pinMode(resetPin, OUTPUT);
  pinMode(ssLchPin, OUTPUT);
  pinMode(ssRchPin, OUTPUT);

  digitalWrite(resetPin, HIGH);
  this->disableSlaveSelect();

  SPI.begin();
}

void YMF825::resetHardware() {
  digitalWrite(resetPin, LOW);
  delay(1);
  digitalWrite(resetPin, HIGH);
}

bool YMF825::isBusy() {
  return false;
}

void YMF825::setTargetChip(uint8_t targetChip) {
  this->targetChip = targetChip;
}

uint8_t YMF825::getTargetChip() {
  return this->targetChip;
}

void YMF825::write(uint8_t address, uint8_t data) {
  SPI.beginTransaction(spiSettings);
  {
    this->enableSlaveSelect();
    SPI.transfer(address);
    SPI.transfer(data);
    this->disableSlaveSelect();
  }
  SPI.endTransaction();
}

void YMF825::burstwrite(uint8_t address, uint8_t *data, uint16_t size) {
  SPI.beginTransaction(spiSettings);
  {
    this->enableSlaveSelect();
    SPI.transfer(address);
    SPI.transfer(data, size);
    this->disableSlaveSelect();
  }
  SPI.endTransaction();
}

uint8_t YMF825::read(uint8_t targetChip, uint8_t address) {
  uint8_t data;

  SPI.beginTransaction(spiSettings);
  {
    this->enableSlaveSelectExclusive(targetChip);
    SPI.transfer(0x80 | address);
    data = SPI.transfer(data);
    this->disableSlaveSelect();
  }
  SPI.endTransaction();

  return data;
}

void YMF825::enableSlaveSelect() {
  // LOW is active, HIGH is inactive
  digitalWrite(ssLchPin, (targetChip & YMF825_TARGET_LCH) ? LOW : HIGH);
  digitalWrite(ssRchPin, (targetChip & YMF825_TARGET_RCH) ? LOW : HIGH);
}

void YMF825::enableSlaveSelectExclusive(uint8_t targetChip) {
  digitalWrite((targetChip & YMF825_TARGET_LCH) ? ssLchPin : ssRchPin, LOW);
  digitalWrite((targetChip & YMF825_TARGET_LCH) ? ssRchPin : ssLchPin, HIGH);
}

void YMF825::disableSlaveSelect() {
  digitalWrite(ssLchPin, HIGH);
  digitalWrite(ssRchPin, HIGH);
}
