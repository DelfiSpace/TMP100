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
 #include "hal_uart.h"

 //Internal Register Address
 #define TEMP_REG					        0x00
 #define CONFIG_REG					      0x01
 #define TEMP_THRESH_HIGH_REG		  0x02
 #define TEMP_THRESH_LOW_REG			0x03

 //Conversion Constant (in degC*E-4)
 # define	MUL_9_bit				  5000
 # define	MUL_10_bit				2500
 # define	MUL_11_bit				1250
 # define	MUL_12_bit				625



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
 uint8_t tmp_readRegister(dev_id id, uint8_t reg, uint16_t *res)
 {

   HAL_I2C_readWrite(id, &reg, 1, res, 1);

   return 0;
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
 uint8_t tmp_writeRegister(dev_id id, uint8_t reg, uint8_t val)
 {

     uint8_t tx_buf[2] = { reg, val };

     HAL_I2C_readWrite(id, tx_buf, 2, NULL, 0);
 }


/**  Initialise the value of config register
 *
 *   Parameters:
 *   unsigned char res		User defined resolution (9, 10, 11 or 12 bit)
 *
 */
void tmp_init(dev_id id, uint16_t *mul, uint8_t res)
{
	//default mode: disable shutdown, comparator mode, active low, 1 consecutive fault
	tmp_writeRegister(id, CONFIG_REG, res);

	switch(res)
	{
  	case TMP100_RESOLUTION_9_BIT:
    	*mul = MUL_9_bit;
    	break;

  	case TMP100_RESOLUTION_10_BIT:
    	*mul = MUL_10_bit;
    	break;

  	case TMP100_RESOLUTION_11_BIT:
    	*mul = MUL_11_bit;
    	break;

  	case TMP100_RESOLUTION_12_BIT:
    	*mul = MUL_12_bit;
    	break;
	}
}

/**  Get the temperature in degC*E-4
 *
 *   Parameters:
 *   long & 		       temperature in degC*E-4
 *
 *
 *	 Returns
 * 	 unsigned char         0 success
 *                         1 fail
 *
 *   Note:
 *	 Return is in long and degC*E-4 to prevent usage of float datatype
 *
 */
uint8_t tmp_getTemperature(const dev_id id,
                              const uint16_t mul,
                              int32_t *res) {
	uint16_t adc_code = -1;
  uint8_t shift = 0;

	tmp_readRegister(id, TEMP_REG, &adc_code);

	if (mul == MUL_12_bit) {
		shift = 4;			//first 4 LSB is 0
	} else if (mul == MUL_11_bit) {
		shift = 5;			//first 5 LSB is 0
	} else if (mul == MUL_10_bit) {
		shift = 6;			//first 6 LSB is 0
	} else if (mul == MUL_9_bit) {
		shift = 7;		//first 7 LSB is 0
	} else {
    return 1;
  }

  *res = (int32_t)(adc_code >> shift) * mul;

	return 0;
 }


