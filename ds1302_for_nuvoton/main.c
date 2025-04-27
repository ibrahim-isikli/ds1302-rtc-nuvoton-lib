/****************************************************************************
 * @file     main.c
 * @version  V1.01
 * $Revision: 1 $
 * $Date: 2019/05/02 8:05p $
 * @brief    ds1302_for_nuvoton Sample
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2011 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "ds1302_for_nuvoton.h"
#include "ds1302.h"

#if defined(__GNUC__) && !defined(__ARMCC_VERSION) && defined(OS_USE_SEMIHOSTING)
    extern void initialise_monitor_handles(void);
#endif

extern void Periph_Init(void);
extern void Clock_Init(void);
extern void Pin_Init(void);

uint8_t time_set[8] = {0x00, 25, 4, 27, 20, 43, 0, 7}; // 2024-04-27 20:23:00 sunday
uint8_t time_read[8] = {0};

void System_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    Clock_Init();
    Pin_Init();
    Periph_Init();

    /* Lock protected registers */
    SYS_LockReg();
}

int32_t main(void)
{
    /* Init System, IP clock, multi-function I/O and Peripheral*/
    System_Init();
    printf("*** Init Done, User add operation code***\n");
    DS1302_Init();
    DS1302_WriteTime(time_set);

    while (1)
    {
    	// wait 1 second
    	for (int i = 0; i < 10; i++)
    	{
    	    CLK_SysTickDelay(100000); // 100 ms delay
    	}

    	DS1302_ReadTime(time_read);
    	printf("Read Date/Time: 20%02d-%02d-%02d %02d:%02d:%02d (Day:%d)\n",
    	        time_read[1], time_read[2], time_read[3],
    	        time_read[4], time_read[5], time_read[6],
    	        time_read[7]);

    }

}
