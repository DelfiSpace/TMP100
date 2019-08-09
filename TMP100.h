/* Code written by Chia Jiun Wei @ 1 Mar 2017
 * <J.W.Chia@tudelft.nl>
 
 * TMP100: a library to provide high level APIs to interface with the 
 * Texas Instruments temperature sensor. It is possible to use this 
 * library in Energia (the Arduino port for MSP microcontrollers) or 
 * in other toolchains.
 
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License 
 * version 3, both as published by the Free Software Foundation.
  
 */
 
#ifndef TMP100_H
#define TMP100_H

#include "DWire.h"

//Internal Register Address
#define TEMP_REG					0x00
#define CONFIG_REG					0x01
#define TEMP_THRESH_HIGH_REG		0x02
#define TEMP_THRESH_LOW_REG			0x03

//Config Register Settings 
//Shutdown Mode
#define ENABLE_SHUTDOWN				0x01
#define DISABLE_SHUTDOWN			0x00

//Thermostat mode
#define COMPARATOR_MODE				0x00
#define INTERRUPT_MODE				0x02

//Polarity 
#define POLARITY_LOW				0x00		//Active Low
#define POLARITY_HIGH				0x04		//Active High

//Fault queue
#define CONSECUTIVE_FAULTS_1		0x00
#define CONSECUTIVE_FAULTS_2		0x08
#define CONSECUTIVE_FAULTS_4		0x10	
#define CONSECUTIVE_FAULTS_6		0x18	

//Converter Resolution
#define RESOLUTION_9_BIT			0x00		//0.5 degC
#define RESOLUTION_10_BIT			0x20		//0.25 degC
#define RESOLUTION_11_BIT			0x40		//0.125 degC
#define RESOLUTION_12_BIT			0x60		//0.0625 degC

//Conversion Constant (in degC*E-4)
# define	MUL_9_bit				5000
# define	MUL_10_bit				2500
# define	MUL_11_bit				1250
# define	MUL_12_bit				625

class TMP100

{
protected:	
	DWire &wire;
    unsigned char address;
	unsigned short mul;

public:
	
	TMP100(DWire &i2c, unsigned char addr);
	virtual ~TMP100( ) {};
	
	void init(unsigned char res);
	unsigned char getTemperature(long &t);
	
	
	// read and write from the register
	unsigned char readRegister(unsigned char reg, unsigned short &output);
	unsigned char writeRegister(unsigned char reg, unsigned char val);
	
private:	
	
};

#endif  // TMP100_H
