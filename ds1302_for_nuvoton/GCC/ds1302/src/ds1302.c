/*
 *  ds1302.c
 *  Created on: Apr 27, 2025
 *
 *  © 2025 Author: ibrahim isikli - This project is licensed under the MIT License.
 *	Feel free to use, share, and contribute with attribution!
 */

#include "DS1302.h"

//GPIO
#define DS1302_SCLK_PORT      PA
#define DS1302_SCLK_PIN       0
#define DS1302_SDA_PORT       PA
#define DS1302_SDA_PIN        1
#define DS1302_RST_PORT       PA
#define DS1302_RST_PIN        2

#define DS1302_SCLK_HIGH()    (DS1302_SCLK_PORT->DOUT |= (1 << DS1302_SCLK_PIN))
#define DS1302_SCLK_LOW()     (DS1302_SCLK_PORT->DOUT &= ~(1 << DS1302_SCLK_PIN))

#define DS1302_SDA_HIGH()     (DS1302_SDA_PORT->DOUT |= (1 << DS1302_SDA_PIN))
#define DS1302_SDA_LOW()      (DS1302_SDA_PORT->DOUT &= ~(1 << DS1302_SDA_PIN))

#define DS1302_RST_HIGH()     (DS1302_RST_PORT->DOUT |= (1 << DS1302_RST_PIN))
#define DS1302_RST_LOW()      (DS1302_RST_PORT->DOUT &= ~(1 << DS1302_RST_PIN))

#define DS1302_SDA_READ()     ((DS1302_SDA_PORT->PIN & (1 << DS1302_SDA_PIN)) ? 1 : 0)

// HEX <-> BCD
#define HEX2BCD(v)	((v) % 10 + (v) / 10 * 16)
#define BCD2HEX(v)	((v) % 16 + (v) / 16 * 10)

// DS1302 commands
#define DS1302_SEC				0x80
#define DS1302_MIN				0x82
#define DS1302_HOUR				0x84
#define DS1302_DATE				0x86
#define DS1302_MONTH			0x88
#define DS1302_DAY				0x8A
#define DS1302_YEAR				0x8C
#define DS1302_CONTROL			0x8E
#define DS1302_CHARGER			0x90
#define DS1302_CLKBURST			0xBE
#define DS1302_RAMBURST 		0xFE

#define RAMSIZE 				0x31
#define DS1302_RAMSTART			0xC0


// SDA pin is output
static void writeSDA(void)
{
    GPIO_SetMode(DS1302_SDA_PORT, (1 << DS1302_SDA_PIN), GPIO_MODE_OUTPUT);
}

// SDA pin is input
static void readSDA(void)
{
    GPIO_SetMode(DS1302_SDA_PORT, (1 << DS1302_SDA_PIN), GPIO_MODE_INPUT);
}

// send command
static void DS1302_SendCmd(uint8_t cmd)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        if (cmd & 0x01)
            DS1302_SDA_HIGH();
        else
            DS1302_SDA_LOW();

        DS1302_SCLK_HIGH();
        CLK_SysTickDelay(1);
        DS1302_SCLK_LOW();
        CLK_SysTickDelay(1);
        cmd >>= 1;
    }
}

// write byte
static void DS1302_WriteByte(uint8_t addr, uint8_t d)
{
    uint8_t i;
    DS1302_RST_HIGH();
    DS1302_SendCmd(addr);

    for (i = 0; i < 8; i++) {
        if (d & 0x01)
            DS1302_SDA_HIGH();
        else
            DS1302_SDA_LOW();

        DS1302_SCLK_HIGH();
        CLK_SysTickDelay(1);
        DS1302_SCLK_LOW();
        CLK_SysTickDelay(1);
        d >>= 1;
    }

    DS1302_RST_LOW();
    DS1302_SDA_LOW();
}

// read byte
static uint8_t DS1302_ReadByte(uint8_t addr)
{
    uint8_t i, temp = 0;
    DS1302_RST_HIGH();
    addr |= 0x01;
    DS1302_SendCmd(addr);

    readSDA();
    for (i = 0; i < 8; i++) {
        temp >>= 1;
        if (DS1302_SDA_READ())
            temp |= 0x80;

        DS1302_SCLK_HIGH();
        CLK_SysTickDelay(1);
        DS1302_SCLK_LOW();
        CLK_SysTickDelay(1);
    }
    writeSDA();

    DS1302_RST_LOW();
    DS1302_SDA_LOW();
    return temp;
}

// init RTC
void DS1302_Init(void)
{
    // SCLK, SDA, RST pins are output
    GPIO_SetMode(DS1302_SCLK_PORT, (1 << DS1302_SCLK_PIN), GPIO_MODE_OUTPUT);
    GPIO_SetMode(DS1302_SDA_PORT,  (1 << DS1302_SDA_PIN),  GPIO_MODE_OUTPUT);
    GPIO_SetMode(DS1302_RST_PORT,  (1 << DS1302_RST_PIN),  GPIO_MODE_OUTPUT);

    DS1302_SCLK_LOW();
    DS1302_RST_LOW();
    DS1302_SDA_LOW();

    DS1302_WriteByte(DS1302_CHARGER, 0x00); // trickle charger disable
}

// set time
void DS1302_WriteTime(uint8_t *buf)
{
    DS1302_WriteByte(DS1302_CONTROL, 0x00);
    CLK_SysTickDelay(1);

    DS1302_WriteByte(DS1302_SEC, 0x80);
    DS1302_WriteByte(DS1302_YEAR, HEX2BCD(buf[1]));
    DS1302_WriteByte(DS1302_MONTH, HEX2BCD(buf[2]));
    DS1302_WriteByte(DS1302_DATE, HEX2BCD(buf[3]));
    DS1302_WriteByte(DS1302_HOUR, HEX2BCD(buf[4]));
    DS1302_WriteByte(DS1302_MIN, HEX2BCD(buf[5]));
    DS1302_WriteByte(DS1302_SEC, HEX2BCD(buf[6]));
    DS1302_WriteByte(DS1302_DAY, HEX2BCD(buf[7]));

    DS1302_WriteByte(DS1302_CONTROL, 0x80);
    CLK_SysTickDelay(1);
}

// read time
void DS1302_ReadTime(uint8_t *buf)
{
    uint8_t tmp;

    tmp = DS1302_ReadByte(DS1302_YEAR);
    buf[1] = BCD2HEX(tmp);
    tmp = DS1302_ReadByte(DS1302_MONTH);
    buf[2] = BCD2HEX(tmp);
    tmp = DS1302_ReadByte(DS1302_DATE);
    buf[3] = BCD2HEX(tmp);
    tmp = DS1302_ReadByte(DS1302_HOUR);
    buf[4] = BCD2HEX(tmp);
    tmp = DS1302_ReadByte(DS1302_MIN);
    buf[5] = BCD2HEX(tmp);
    tmp = DS1302_ReadByte(DS1302_SEC) & 0x7F;
    buf[6] = BCD2HEX(tmp);
    tmp = DS1302_ReadByte(DS1302_DAY);
    buf[7] = BCD2HEX(tmp);
}

