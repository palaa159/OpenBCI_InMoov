

#ifndef ____LIS3DH__
#define ____LIS3DH__

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <SPI.h>
#include "pins_arduino.h"
#include "Definitions.h"

class LIS3DH {
public:
  int axisData[3];
  void initialize(byte);
  void enable_accel(byte);
  void disable_accel(void);
  byte getDeviceID(void);
  byte LIS3DH_read(byte);
  void LIS3DH_write(byte,byte);
  int LIS3DH_read16(byte);
  int LIS3DH_readAxis(byte);
  int getX(void);
  int getY(void);
  int getZ(void);
  int getX16(void);
  int getY16(void);
  int getZ16(void);
  boolean LIS3DH_DataReady(void);
  boolean LIS3DH_DataAvailable(void);
  void readAllRegs(void);
  void writeLIS3DHdata(void);
  void LIS3DH_updateAxisData(void);
	
private:
  void csLow();
  void csHigh();
  int DRDYpinValue;
  int lastDRDYpinValue;

};

#endif
