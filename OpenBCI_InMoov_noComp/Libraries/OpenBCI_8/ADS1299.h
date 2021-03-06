

#ifndef ____ADS1299__
#define ____ADS1299__

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <SPI.h>
#include "pins_arduino.h"
#include "Definitions.h"

class ADS1299 {
public:
    
    void initialize();
    
    //ADS1299 SPI Command Definitions (Datasheet, p35)
    //System Commands
    void WAKEUP();
    void STANDBY();
    void RESET();
    void START();
    void STOP();
    
    //Data Read Commands
    void RDATAC();
    void SDATAC();
    void RDATA();
    
    //Register Read/Write Commands
    
    byte RREG(byte _address);
    void RREGS(byte _address, byte _numRegistersMinusOne);
    void WREG(byte _address, byte _value); 
    void WREGS(byte _address, byte _numRegistersMinusOne);
	byte getDeviceID();
	void printRegisterName(byte _address);
    void printHex(byte _data);
    void updateChannelData();
    
    //SPI Transfer function
    byte xfer(byte _data);

    int DRDY, CS, RST; 		// pin numbers for DataRead ChipSelect Reset pins 
    int DIVIDER;		// select SPI SCK frequency
    int stat;			// used to hold the status register
    byte regData [24];	        // array is used to mirror register data
    long channelData [9];	// array used when reading channel data as ints
    byte bit24ChannelData[24];    // array to hold raw channel data
    char channelSettings[8][6];  // array to hold current channel settings
    char defaultChannelSettings[6];  // default channel settings
    boolean useInBias[8];        // used to remember if we were included in Bias before channel power down
    boolean useSRB1;             // used to keep track of if we are using SRB1
    boolean useSRB2[8];          // used to remember if we were included in SRB2 before channel power down
    char leadOffSettings[8][2];  // used to control on/off of impedance measure for P and N side of each channel
    boolean verbosity;		 // turn on/off Serial feedback
	
    void resetADS(void);                      //reset all the ADS1299's settings.  Call however you'd like
    void startADS(void);
    void stopADS(void);
	
    void writeChannelSettings(void);
    void writeChannelSettings(int);
    void activateChannel(int);    // activate a given channel 1-8
    void reportDefaultChannelSettings(void);
    void deactivateChannel(int);  //disable given channel 1-8
    
    void configureLeadOffDetection(byte, byte);
    void changeChannelLeadOffDetection(void);
    void configureInternalTestSignal(byte, byte);  
    
    boolean isDataAvailable(void);
    void writeADSchannelData(void);
    void printAllRegisters(void);
    void setSRB1(boolean desired_state);
    void printDeviceID(void);
	
private:
    byte old_SPCR;
    byte old_SPSR;
    boolean _OpenBCI_03;
    boolean use_N_inputs;
    boolean use_SRB2[OPENBCI_NCHAN];
    boolean isRunning;
    boolean use_SRB1(void);
    void csLow();
    void csHigh();

};

#endif
