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

#ifndef __TMP100_H
#define __TMP100_H

#include "satellite.h"
#include <stdint.h>

//Config Register Settings
//Shutdown Mode
#define TMP100_ENABLE_SHUTDOWN				0x01
#define TMP100_DISABLE_SHUTDOWN			0x00

//Thermostat mode
#define TMP100_COMPARATOR_MODE				0x00
#define TMP100_INTERRUPT_MODE				0x02

//Polarity
#define TMP100_POLARITY_LOW				0x00		//Active Low
#define TMP100_POLARITY_HIGH				0x04		//Active High

//Fault queue
#define TMP100_CONSECUTIVE_FAULTS_1		0x00
#define TMP100_CONSECUTIVE_FAULTS_2		0x08
#define TMP100_CONSECUTIVE_FAULTS_4		0x10
#define TMP100_CONSECUTIVE_FAULTS_6		0x18

//Converter Resolution
#define TMP100_RESOLUTION_9_BIT			0x00		//0.5 degC
#define TMP100_RESOLUTION_10_BIT			0x20		//0.25 degC
#define TMP100_RESOLUTION_11_BIT			0x40		//0.125 degC
#define TMP100_RESOLUTION_12_BIT			0x60		//0.0625 degC

void tmp_init(dev_id id, uint16_t *mul, uint8_t res);
uint8_t tmp_getTemperature(const dev_id id, const uint16_t mul, int32_t *res);

#endif  // TMP100_H
