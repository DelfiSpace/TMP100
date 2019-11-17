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
 */
void TMP100::init()
{
	// default mode: disable shutdown, comparator mode, active low, 1 consecutive fault
    // 12 bit resolution
	writeRegister(CONFIG_REG, RESOLUTION_12_BIT);
}
 
/**  Get the temperature in degC * E-1
 *
 *   Parameters:
 *   long & 		                temperature in units of 0.1 degC
 *                                  SHRT_MAX in case of failure
 *
 *
 *	 Returns
 * 	 unsigned char         0 success
 *                         1 fail
 *
 */
 unsigned char TMP100::getTemperature(signed short &t)
 {
	unsigned short adc_code;
	
	unsigned char ret = readRegister(TEMP_REG, adc_code);
	
	if (!ret)
	{
	    t = ((adc_code >> 4) + (adc_code >> 7) >> 1);
	}
	else
	{
	    t = SHRT_MAX;
	}
	return ret;
 }
 



/**  Returns the value (2 byte) of the selected internal register
 *
 *   Parameters:
 *   unsigned char reg     register number
 *   unsigned short &      register value
 *
 *
 *   Returns:
 *   unsigned char         0 success
 *                         1 fail
 *
 */
unsigned char TMP100::readRegister(unsigned char reg, unsigned short &output)
{
    wire.beginTransmission(address);
    wire.write(reg);
	
    unsigned char res = wire.requestFrom(address, 2);
    if (res == 2)
    {
		((unsigned char*)&output)[1] = wire.read();
		((unsigned char*)&output)[0] = wire.read();
		return 0;
    }
	else
	{
	    output = 0;
		return 1;
	}
}


/**  Set the value (1 byte) of the selected internal register
 *   
 *   Parameters:
 *   unsigned char reg     register number
 *   unsigned char val     register value
 *
 *   Returns:
 *   unsigned char         0 success
 *                         1 fail
 *
 */
unsigned char TMP100::writeRegister(unsigned char reg, unsigned char val)
{
    wire.beginTransmission(address);
    wire.write(reg);
    wire.write(val & 0xFF);      
    return wire.endTransmission();
}
