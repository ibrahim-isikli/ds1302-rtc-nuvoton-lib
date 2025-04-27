/*
 * ds1302.h
 *
 *  Created on: Apr 27, 2025
 *      Author: ibrahim
 */

#ifndef DS1302_INC_DS1302_H_
#define DS1302_INC_DS1302_H_
#include "NuMicro.h"

static void writeSDA(void);
static void readSDA(void);
static void DS1302_SendCmd(uint8_t cmd);
static void DS1302_WriteByte(uint8_t addr, uint8_t d);
static uint8_t DS1302_ReadByte(uint8_t addr);
void DS1302_Init(void);
void DS1302_WriteTime(uint8_t *buf);
void DS1302_ReadTime(uint8_t *buf);

#endif /* DS1302_INC_DS1302_H_ */
