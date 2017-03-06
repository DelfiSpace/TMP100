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
 
 #include "TMP100.h"
 
/**  TMP100 class creator function
 *
 *   Parameters:
 *   DWire &i2c             I2C object
 *	 unsigned char addr		I2C address (7 bits)
 *
 */
TMP100::TMP100(DWire &i2c, unsigned char addr): wire(i2c)
{
    address = addr;
}

/**  Initialise the value of config register
 *
 *   Parameters:
 *   unsigned char res		User defined resolution (9, 10, 11 or 12 bit)
 *
 */
void TMP100::init(unsigned char res)
{
	//default mode: disable shutdown, comparator mode, active low, 1 consecutive fault
	writeRegister(CONFIG_REG, res);	 

	switch(res)
	{
	case RESOLUTION_9_BIT:
	mul = MUL_9_bit;
	break;
	
	case RESOLUTION_10_BIT:
	mul = MUL_10_bit;
	break;
	
	case RESOLUTION_11_BIT:
	mul = MUL_11_bit;
	break;
	
	case RESOLUTION_12_BIT:
	mul = MUL_12_bit;
	break;
	}
}
 
/**  Get the temperature in degC*E-4
 *
 *	 Returns
 *	 long					temperature in degC*E-4
 *
 *   Note:
 *	 Return is in long and degC*E-4 to prevent usage of float datatype
 * 
 */
 long TMP100::getTemperature()
 {
	unsigned short adc_code = -1;
	long temp;
	
	adc_code = readRegister(TEMP_REG);
	
	if (mul == MUL_12_bit)
	{
		temp = (long)(adc_code >> 4) * mul;		//first 4 LSB is 0
	}
	else if (mul == MUL_11_bit)
	{
		temp = (long)(adc_code >> 5) * mul;		//first 5 LSB is 0
	}
	else if (mul == MUL_10_bit)
	{
		temp = (long)(adc_code >> 6) * mul;		//first 6 LSB is 0
	}
	else if (mul == MUL_9_bit)
	{
		temp = (long)(adc_code >> 7) * mul;		//first 7 LSB is 0
	}
	
	return temp;
 }
 



/**  Returns the value (2 byte) of the selected internal register
 *
 *   Parameters:
 *   unsigned char reg     register number
 *
 *   Returns:
 *   unsigned short         register value
 *
 */
unsigned short TMP100::readRegister(unsigned char reg)
{
    unsigned short ret = -1;
    wire.beginTransmission(address);
    wire.write(reg);
	
    unsigned char res = wire.requestFrom(address, 2);
    if (res == 2)
    {
		((unsigned char*)&ret)[1] = wire.read();
		((unsigned char*)&ret)[0] = wire.read();
    }

    return ret;
}


/**  Set the value (1 byte) of the selected internal register
 *   
 *   Parameters:
 *   unsigned char reg     register number
 *   unsigned char val     register value
 *
 */
void TMP100::writeRegister(unsigned char reg, unsigned char val)
{
    wire.beginTransmission(address);
    wire.write(reg);
    wire.write(val & 0xFF);      
    wire.endTransmission();
}
