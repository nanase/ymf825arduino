#pragma once

#include "Arduino.h"

#define YMF825_SPI_MAX_SPEED 10000000

enum YMF825TargetChip {
  YMF825_TARGET_NONE = 0x00,
  YMF825_TARGET_LCH  = 0x01,
  YMF825_TARGET_RCH  = 0x02,

  YMF825_TARGET_ALL = YMF825_TARGET_LCH | YMF825_TARGET_RCH,

  YMF825_TARGET_MONO   = YMF825_TARGET_LCH,
  YMF825_TARGET_STEREO = YMF825_TARGET_LCH | YMF825_TARGET_RCH,
};

class YMF825Device {
 protected:
 public:
  virtual void initialize() = 0;

  virtual void resetHardware() = 0;

  virtual bool isBusy() = 0;

  virtual void setTargetChip(uint8_t targetChip) = 0;
  virtual uint8_t getTargetChip()                = 0;

  virtual void write(uint8_t address, uint8_t data)                      = 0;
  virtual void burstwrite(uint8_t address, uint8_t *data, uint16_t size) = 0;

  virtual uint8_t read(uint8_t targetChip, uint8_t address) = 0;
};

class YMF825 : public YMF825Device {
 private:
  uint8_t resetPin;
  uint8_t ssLchPin;
  uint8_t ssRchPin;
  uint8_t targetChip;

 public:
  YMF825(uint8_t resetPin, uint8_t ssPin);
  YMF825(uint8_t resetPin, uint8_t ssLchPin, uint8_t ssRchPin);

  void initialize();

  void resetHardware();

  bool isBusy();

  void setTargetChip(uint8_t targetChip);
  uint8_t getTargetChip();

  void write(uint8_t address, uint8_t data);
  void burstwrite(uint8_t address, uint8_t *data, uint16_t size);

  uint8_t read(uint8_t targetChip, uint8_t address);

 private:
  void enableSlaveSelect();
  void enableSlaveSelectExclusive(uint8_t targetChip);
  void disableSlaveSelect();
};
