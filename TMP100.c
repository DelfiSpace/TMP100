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
 #include "hal_functions.h"

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
 bool tmp_readRegister(dev_id id, uint8_t reg, uint16_t *res)
 {

   bool res1 = HAL_I2C_readWrite(id, &reg, 1, res, 2);

   uint16_t temp;
   temp = *res;
   *res = ((0x00ff & temp) << 8);
   *res |= (temp >> 8);

   return res1;
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
 bool tmp_writeRegister(dev_id id, uint8_t reg, uint8_t val)
 {

     uint8_t tx_buf[2] = { reg, val };

     bool res = HAL_I2C_readWrite(id, tx_buf, 2, NULL, 0);

     return res;
 }


/**  Initialise the value of config register
 *
 *   Parameters:
 *   unsigned char res		User defined resolution (9, 10, 11 or 12 bit)
 *
 */
void tmp_init(dev_id id)
{
	//default mode: disable shutdown, 12 bits, comparator mode, active low, 6 consecutive fault
  tmp_writeRegister(id, CONFIG_REG, 0x78);

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
bool tmp_getTemperature_raw(const dev_id id, int16_t *res) {
	int16_t adc_code = -1;


	bool res1 = tmp_readRegister(id, TEMP_REG, &adc_code);

  *res = (int16_t)adc_code >> 4;

	return res1;
 }

 uint8_t tmp_getRawTemperature(const dev_id id,
                                const int16_t raw,
                                float *res) {

  *res = (float)raw * 0.0625;
 	return 0;
}
